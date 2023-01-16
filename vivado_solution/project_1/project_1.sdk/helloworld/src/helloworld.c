
/*****************************************************************************/
/**
 *
 * @file main.c
 *
 * Rodrigo modified version of Shiming modified based on xaxidma_example_sg_intr.c
 *
 * Many lines are deleted from this file and this is not expected to run at
 *  all. This file is only intended to give you an idea how to use the DMA
 *  for Tx and Rx, because the SDK example has only Tx and does not show how
 *  to send multiple BDs.
 *
 * Please don't let this file limit your imagination. Implement your project
 *  in any way you want, and only look at this file for the details of the
 *  transmission and receiving (mainly in the very last function).
 */

/*
NOW IS IMPLEMENTED VIA HEADER BUT HERE ARE SOME RESOURCES ON UART
https://support.xilinx.com/s/question/0D52E00006hpbQtSAI/how-to-read-uart1-txt-file-input?language=en_US
https://support.xilinx.com/s/question/0D52E00006hpZ0mSAE/how-to-read-data-and-print-it-from-the-serial-port-using-hyperterminal-whats-wrong-with-my-code?language=en_US
https://www.fpgadeveloper.com/2014/02/create-an-application-using-the-sdk.html/

*/

/***************************** Include Files *********************************/
	#include "xaxidma.h"
	#include "xil_io.h"
	#include "xparameters.h"
	#include "xil_exception.h"
	#include "xdebug.h"
	#include "xuartps.h"
	#include "network_data.h"

	#include "math.h"


	#ifdef __aarch64__
	#include "xil_mmu.h"
	#endif

	#ifdef XPAR_UARTNS550_0_BASEADDR
	#include "xuartns550_l.h"       /* to use uartns550 */
	#endif

	#ifndef DEBUG
	extern void xil_printf(const char *format, ...);
	#endif

	#ifdef XPAR_INTC_0_DEVICE_ID
	#include "xintc.h"
	#else
	#include "xscugic.h"
	#endif

/******************** Constant Definitions **********************************/
/* Shiming:
 * Accelerator application specific consts
 * */
	#define ACC_DATA_SIZE 4
	#define ACC_VEC_LEN 49
	#define	ARRAYSIZE(x)	(sizeof(x) / sizeof(x[ 0 ]))

	#define SCATTERED_DATA_BD_COUNT ACC_VEC_LEN
	#define SCATTERED_DATA_BD_LEN ACC_DATA_SIZE
	#define CONSECUTIVE_DATA_BD_COUNT 1
	#define CONSECUTIVE_DATA_BD_LEN (ACC_VEC_LEN * ACC_DATA_SIZE)
	#define TX_BD_COUNT SCATTERED_DATA_BD_COUNT

	#define RX_BD_COUNT 1
	#define RX_BD_LEN ACC_DATA_SIZE

	/* Shiming:
	* HDR-NN parameters
	* */
	#define HIDDEN_SIZE 30
	#define OUTPUT_SIZE 10
	#define FIXED_POINT_PRECISION_LEN 12
	#define SHIFT_MASK ((1 << FIXED_POINT_PRECISION_LEN) - 1) // 65535 (all LSB set, all MSB clear)

	/* Shiming:
	* Device hardware build related constants.
	*/
	#define DMA_DEV_ID		XPAR_AXIDMA_0_DEVICE_ID

	#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
	#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
	#elif XPAR_MIG7SERIES_0_BASEADDR
	#define DDR_BASE_ADDR	XPAR_MIG7SERIES_0_BASEADDR
	#elif XPAR_MIG_0_BASEADDR
	#define DDR_BASE_ADDR	XPAR_MIG_0_BASEADDR
	#elif XPAR_PSU_DDR_0_S_AXI_BASEADDR
	#define DDR_BASE_ADDR	XPAR_PSU_DDR_0_S_AXI_BASEADDR
	#endif

	#ifndef DDR_BASE_ADDR
	#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
				DEFAULT SET TO 0x01000000
	#define MEM_BASE_ADDR		0x01000000

	#else
	#define MEM_BASE_ADDR		(DDR_BASE_ADDR + 0x1000000)
	#endif

	#ifdef XPAR_INTC_0_DEVICE_ID
	#define RX_INTR_ID		XPAR_INTC_0_AXIDMA_0_S2MM_INTROUT_VEC_ID
	#define TX_INTR_ID		XPAR_INTC_0_AXIDMA_0_MM2S_INTROUT_VEC_ID
	#else
	#define RX_INTR_ID		XPAR_FABRIC_AXIDMA_0_S2MM_INTROUT_VEC_ID
	#define TX_INTR_ID		XPAR_FABRIC_AXIDMA_0_MM2S_INTROUT_VEC_ID
	#endif

	#define RX_BD_SPACE_BASE	(MEM_BASE_ADDR)
	#define RX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x0000FFFF)
	#define TX_BD_SPACE_BASE	(MEM_BASE_ADDR + 0x00010000)
	#define TX_BD_SPACE_HIGH	(MEM_BASE_ADDR + 0x0001FFFF)
	/* We don't need tx buffer in this application */
	#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00300000)
	#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x004FFFFF)

	#ifdef XPAR_INTC_0_DEVICE_ID
	#define INTC_DEVICE_ID          XPAR_INTC_0_DEVICE_ID
	#else
	#define INTC_DEVICE_ID          XPAR_SCUGIC_SINGLE_DEVICE_ID
	#endif

	/* Timeout loop counter for reset
	*/
	#define RESET_TIMEOUT_COUNTER	10000

	/*
	* Buffer and Buffer Descriptor related constant definition
	*/
	#define MARK_UNCACHEABLE        0x701

	/* The interrupt coalescing threshold and delay timer threshold
	* Valid range is 1 to 255
	*
	* We set the coalescing threshold to be the total number of packets.
	* The receive side will only get one completion interrupt for this example.
	*/
	#define COALESCING_COUNT		ACC_VEC_LEN
	#define DELAY_TIMER_COUNT		100

	#ifdef XPAR_INTC_0_DEVICE_ID
	#define INTC		XIntc
	#define INTC_HANDLER	XIntc_InterruptHandler
	#else
	#define INTC		XScuGic
	#define INTC_HANDLER	XScuGic_InterruptHandler
	#endif

	/*
	* AXI4-Lite slave registers on PL.
	* This is device-specific.
	* */
	#define AXI4L_SLV_BASEADDR 0x43C00000
	#define AXI4L_SLV_REG_0_ADDR (AXI4L_SLV_BASEADDR + 0)
	#define AXI4L_SLV_REG_1_ADDR (AXI4L_SLV_BASEADDR + 0x4)
	#define AXI4L_SLV_REG_2_ADDR (AXI4L_SLV_BASEADDR + 0x8)
	#define AXI4L_SLV_REG_3_ADDR (AXI4L_SLV_BASEADDR + 0xC)

/**************************** Type Definitions *******************************/
/***************** Macros (Inline Functions) Definitions *********************/
	/** Shiming: (Look at line 229 for longer explanation)
	 * These are written to the memory-mapped registers of an AXI-Lite bus.
	 * These can be read by the PL logic and I use them to send control signals.
	 */
	#define AccWriteStart() (Xil_Out32(AXI4L_SLV_REG_0_ADDR, 0x00000002))
	#define AccWriteStop() (Xil_Out32(AXI4L_SLV_REG_0_ADDR, 0x00000000))
	#define AccWriteSelA() (Xil_Out32(AXI4L_SLV_REG_0_ADDR, 0x00000000))
	#define AccWriteSelB() (Xil_Out32(AXI4L_SLV_REG_0_ADDR, 0x00000001))
	#define AccWriteValidValue() (Xil_Out32(AXI4L_SLV_REG_0_ADDR, 0x00000004))

/************************** Function Prototypes ******************************/
	#ifdef XPAR_UARTNS550_0_BASEADDR
	static void Uart550_Setup(void);
	#endif

	static void TxCallBack(XAxiDma_BdRing * TxRingPtr);
	static void TxIntrHandler(void *Callback);
	static void RxCallBack(XAxiDma_BdRing * RxRingPtr);
	static void RxIntrHandler(void *Callback);

	static int SetupIntrSystem(INTC * IntcInstancePtr,
				XAxiDma * AxiDmaPtr, u16 TxIntrId, u16 RxIntrId);
	static void DisableIntrSystem(INTC * IntcInstancePtr,
						u16 TxIntrId, u16 RxIntrId);

	static int TxSetup(XAxiDma * AxiDmaInstPtr);
	static int RxSetup(XAxiDma * AxiDmaInstPtr);
	static int SendConsecutivePacket(XAxiDma * AxiDmaInstPtr, \
			UINTPTR BufferBaseAddr, int PadZeroNum);
	static int SendScatteredPacket(XAxiDma * AxiDmaInstPtr, \
			UINTPTR BufferBaseAddr, int PadZeroNum, int ScatterInterval);
	static int SendRxBd(XAxiDma * AxiDmaInstPtr);

	static int outputNeuron(int* image_input, int* weights);
	static int multiplyVectors(int* input, int* weights);
	static void networkPSrun();
	static int networkPSsigmoid(int z);

/************************** Variable Definitions *****************************/
	/*
	* Device instance definitions
	*/
	XAxiDma AxiDma;

	static INTC Intc;	/* Instance of the Interrupt Controller */

	/*
	* Flags interrupt handlers use to notify the application context the events.
	*/
	volatile int TxDone;
	volatile int RxDone;
	volatile int Error;

	/* Shiming:
	* A buffer specifically for sending zeroes
	* */
	static const int ZeroBuffer[ACC_VEC_LEN] = {0};
	/* Shiming:
	* Buffers used by hdr-nn
	* */

	static int networkPSargmax(int* result){
		int max_index = 0;
		for (int i = 0; i < 10; i++)
			if (result[i] > result[max_index])
				max_index = i;
		return max_index;
	}

	static int networkPSsigmoid(int z){
		/*	def sigmoid(z):
		    """The sigmoid function."""
		    return 1.0/(1.0+np.exp(-z))*/
		float float_temp = z /pow(2.0, FIXED_POINT_PRECISION_LEN);
		float temp_result = 1.0/(1.0+exp(-float_temp));
		int final_result = temp_result *pow(2, FIXED_POINT_PRECISION_LEN);
		return final_result;
	}
	// size_of_input = 784
	// size_of_result = 30
	static void networkPSfeedforward(int* weights, int* biases, int* input_vector, int size_of_input, int size_of_result, int* result){
		int temp_neuron = 0;
		long long int temp_weight, temp_input, temp_tensor;
		for (int hidden_neuron = 0; hidden_neuron < size_of_result; hidden_neuron++){
			for (int col = 0; col < size_of_input; col++){
				temp_weight = weights[(hidden_neuron*size_of_input) + col];
				temp_input = input_vector[col];
				if (temp_input){
					xil_printf("");
				}
				temp_tensor = (temp_weight * temp_input) >> FIXED_POINT_PRECISION_LEN;
				temp_neuron += temp_tensor;
			}
			temp_neuron += biases[hidden_neuron];
			temp_neuron= networkPSsigmoid(temp_neuron);
			result[hidden_neuron] = temp_neuron;
			//xil_printf("NEURONA NUMERO %d: %d\n", hidden_neuron, temp_neuron);
			temp_neuron = 0;
		}
	}

	/*
	 * change to fixed point arithmetic:
	 https://stackoverflow.com/questions/10067510/fixed-point-arithmetic-in-c-programming#:~:text=The%20idea%20behind%20fixed%2Dpoint,being%20able%20to%20represent%20fractions.
	 */
	int singleImagePSrun(int image_index){
		int hidden_result[HIDDEN_SIZE];
		int final_output[OUTPUT_SIZE];
		networkPSfeedforward(layer_0, bias_0, &(images[image_index * image_size]), image_size, HIDDEN_SIZE, hidden_result);

		networkPSfeedforward(layer_1, bias_1, hidden_result, HIDDEN_SIZE, OUTPUT_SIZE, final_output);

		return networkPSargmax(final_output);
	}
	static void networkPSrun(){

		for (int image_index = 0; image_index < number_of_images; image_index++){
				xil_printf("ps image %d: %d\n", image_index, 	singleImagePSrun(image_index));
		}

		//quantity = networkPSevaluate(final_results, ground_truth);
	}


int singleImagePLrun(int image_index){
	int* input_image = &(images[image_index*image_size]);
	int hidden_result[HIDDEN_SIZE];
	for(int neuron_result = 0; neuron_result < HIDDEN_SIZE; neuron_result += 1){
		hidden_result[neuron_result] = 0;
		for(int start_index = 0; start_index < image_size; start_index += ACC_VEC_LEN){
			int weight_index = (neuron_result*image_size) + start_index;
			hidden_result[neuron_result] += multiplyVectors(&(input_image[start_index]), &(layer_0[weight_index]));
		}

		hidden_result[neuron_result] += bias_0[neuron_result];
		hidden_result[neuron_result]= networkPSsigmoid(hidden_result[neuron_result]);
		//xil_printf("HIDDEN_RESULT %d: %d\n", neuron_result, hidden_result[neuron_result]);
	}
	int final_output[OUTPUT_SIZE];

	networkPSfeedforward(layer_1, bias_1, hidden_result, HIDDEN_SIZE, OUTPUT_SIZE, final_output);
	int predicted_result = networkPSargmax(final_output);


	/*int weights_temp[ACC_VEC_LEN];
	int input_temp[ACC_VEC_LEN];
	for(int i =0; i<ACC_VEC_LEN; i++){
		weights_temp[i] = 0;
		input_temp[i] = 0;
	}
	for(int neuron_result = 0; neuron_result < OUTPUT_SIZE; neuron_result += 1){
		final_output[neuron_result] = 0;

		for (int i = 0; i<HIDDEN_SIZE; i++){
			int temp_weight = neuron_result * HIDDEN_SIZE + i;
			weights_temp[i] = layer_1[temp_weight];
			input_temp[i] = hidden_result[i];
		}

		final_output[neuron_result] += multiplyVectors(input_temp, weights_temp);


		xil_printf("FINAL_RESULT %d: %d\n", neuron_result, final_output[neuron_result]);
		final_output[neuron_result] += bias_1[neuron_result];
		final_output[neuron_result]= networkPSsigmoid(final_output[neuron_result]);
	}
	int predicted_result = networkPSargmax(final_output);
	xil_printf("PREDICTION USING FPGA: %d", predicted_result);*/
	return predicted_result;
}

void networkPLrun(){
	for (int image_index = 0; image_index < number_of_images; image_index++){
		int image_result = singleImagePLrun(image_index);
		xil_printf("pl/ps image %d: %d\n", image_index, 	image_result);

	}
}


void networkComparePSPLandPS(int n_images){
	xil_printf("Number of images tested: %d\n", n_images);
	int flagMissmatch = 0;
	for (int image_index = 0; image_index < n_images; image_index++){
		int imagePL = singleImagePLrun(image_index);
		int imagePS = singleImagePSrun(image_index);
		if(imagePL != imagePS){
			//xil_printf("missmatch! PS: %d & PS/PL: &d\n", imagePS, imagePL);
			flagMissmatch += 1;
		}
		/*else
			xil_printf("image %d: %d\n", image_index, imagePL);*/

	}
	xil_printf("Matches between PS & PL / total n� images: %d/%d\n", n_images - flagMissmatch, n_images);

}

void testPLrun(){
	int test = multiplyVectors(testInput, testWeights);
	xil_printf("TEST %d\n", test);
}

/*****************************************************************************/

int main(void)
{
	/*
	 * Shiming:
	 * I wrote these 4 lines below to read debug regs.
	 *
	 * For debugging, I let the PL wrote some values to several registers on the AXI bus.
	 * This was the guide I followed:
	 * 		https://www.hackster.io/j-abate/integrating-zynq-ps-and-pl-with-memory-mapped-registers-292a42
	 *
	 * Their purpose are designed in the verilog code (except slv_reg0 which is for
	 * 		the PS to write start/sel), so you can ignore them.
	 * */
	//	u32 slv_reg0_rdata = Xil_In32(0x43C00000);
	//	u32 slv_reg1_rdata = Xil_In32(0x43C00004);
	//	u32 slv_reg2_rdata = Xil_In32(0x43C00008);
	//	u32 slv_reg3_rdata = Xil_In32(0x43C0000C);
		int Status;
		XAxiDma_Config *Config;	// For config. Same as the example from the SDK.

		/* Initial setup for Uart16550 */
	#ifdef XPAR_UARTNS550_0_BASEADDR
		Uart550_Setup();
	#endif

		xil_printf("\r\n--- Entering main() --- \r\n");
	#ifdef __aarch64__
		Xil_SetTlbAttributes(TX_BD_SPACE_BASE, MARK_UNCACHEABLE);
		Xil_SetTlbAttributes(RX_BD_SPACE_BASE, MARK_UNCACHEABLE);
	#endif

	Config = XAxiDma_LookupConfig(DMA_DEV_ID);
	if (!Config) {
		xil_printf("No config found for %d\r\n", DMA_DEV_ID);
		return XST_FAILURE;
	}

	/* Initialize DMA engine */
	XAxiDma_CfgInitialize(&AxiDma, Config);
	if(!XAxiDma_HasSg(&AxiDma)) {
		xil_printf("Device configured as Simple mode \r\n");
		return XST_FAILURE;
	}

	/* Set up TX/RX channels to be ready to transmit and receive packets */
	Status = TxSetup(&AxiDma);
	if (Status != XST_SUCCESS) {
		xil_printf("Failed TX setup\r\n");
		return XST_FAILURE;
	}
	Status = RxSetup(&AxiDma);
	if (Status != XST_SUCCESS) {
		xil_printf("Failed RX setup\r\n");
		return XST_FAILURE;
	}

	/* Set up Interrupt system  */
	Status = SetupIntrSystem(&Intc, &AxiDma, TX_INTR_ID, RX_INTR_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("Failed intr setup\r\n");
		return XST_FAILURE;
	}

	/* Initialize flags before start transfer test  */
	TxDone = 0;
	RxDone = 0;
	Error = 0;

	/*************************True start of the network*******************/
	int exampleReturn = 0;

	//networkPSrun();
	//networkPLrun();
	networkComparePSPLandPS(10);
	networkComparePSPLandPS(100);
	networkComparePSPLandPS(1000);

	//testPLrun();
	//testPLrun();
	//testPLrun();





	/* Disable TX and RX Ring interrupts and return success */
	DisableIntrSystem(&Intc, TX_INTR_ID, RX_INTR_ID);

	/* Print results */
	//xil_printf("Total images: %d, right/wrong: %d/%d\n", ImageCount, Yes, No);


	xil_printf("--- Exiting main() --- \r\n");
	return XST_SUCCESS;
}

/* DMA RING FUNCTIONS */
	/*****************************************************************************/
		/*
		*
		* This is the DMA TX callback function to be called by TX interrupt handler.
		* This function handles BDs (Buffer Descriptors) finished by hardware.
		*
		* @param	TxRingPtr is a pointer to TX channel of the DMA engine.
		*
		* @return	None.
		*
		* @note		None.
		*
	******************************************************************************/
	static void TxCallBack(XAxiDma_BdRing * TxRingPtr)
	{
		int BdCount;
		u32 BdSts;
		XAxiDma_Bd *BdPtr;
		XAxiDma_Bd *BdCurPtr;
		int Status;
		int Index;

		/* Get all processed BDs from hardware */
		BdCount = XAxiDma_BdRingFromHw(TxRingPtr, XAXIDMA_ALL_BDS, &BdPtr);

		/* Handle the BDs */
		BdCurPtr = BdPtr;
		for (Index = 0; Index < BdCount; Index++) {
			/*
			* Check the status in each BD
			* If error happens, the DMA engine will be halted after this
			* BD processing stops.
			*/
			BdSts = XAxiDma_BdGetSts(BdCurPtr);
			if ((BdSts & XAXIDMA_BD_STS_ALL_ERR_MASK) ||
				(!(BdSts & XAXIDMA_BD_STS_COMPLETE_MASK))) {
				Error = 1;
				break;
			}

			/*
			* Here we don't need to do anything. But if a RTOS is being
			* used, we may need to free the packet buffer attached to
			* the processed BD
			*/

			/* Find the next processed BD */
			BdCurPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(TxRingPtr, BdCurPtr);
		}

		/* Free all processed BDs for future transmission */
		Status = XAxiDma_BdRingFree(TxRingPtr, BdCount, BdPtr);
		if (Status != XST_SUCCESS) {
			Error = 1;
		}

		if(!Error) {
			TxDone += BdCount;
		}
	}

	/*****************************************************************************/
		/*
		*
		* This is the DMA TX Interrupt handler function.
		*
		* It gets the interrupt status from the hardware, acknowledges it, and if any
		* error happens, it resets the hardware. Otherwise, if a completion interrupt
		* presents, then it calls the callback function.
		*
		* @param	Callback is a pointer to TX channel of the DMA engine.
		*
		* @return	None.
		*
		* @note		None.
		*
	******************************************************************************/
	static void TxIntrHandler(void *Callback)
	{
		XAxiDma_BdRing *TxRingPtr = (XAxiDma_BdRing *) Callback;
		u32 IrqStatus;
		int TimeOut;

		/* Read pending interrupts */
		IrqStatus = XAxiDma_BdRingGetIrq(TxRingPtr);

		/* Acknowledge pending interrupts */
		XAxiDma_BdRingAckIrq(TxRingPtr, IrqStatus);

		/* If no interrupt is asserted, we do not do anything
		*/
		if (!(IrqStatus & XAXIDMA_IRQ_ALL_MASK)) {
			return;
		}

		/*
		* If error interrupt is asserted, raise error flag, reset the
		* hardware to recover from the error, and return with no further
		* processing.
		*/
		if ((IrqStatus & XAXIDMA_IRQ_ERROR_MASK)) {
			XAxiDma_BdRingDumpRegs(TxRingPtr);
			Error = 1;
			/*
			* Reset should never fail for transmit channel
			*/
			XAxiDma_Reset(&AxiDma);
			TimeOut = RESET_TIMEOUT_COUNTER;
			while (TimeOut) {
				if (XAxiDma_ResetIsDone(&AxiDma)) {
					break;
				}
				TimeOut -= 1;
			}
			return;
		}

		/*
		* If Transmit done interrupt is asserted, call TX call back function
		* to handle the processed BDs and raise the according flag
		*/
		if ((IrqStatus & (XAXIDMA_IRQ_DELAY_MASK | XAXIDMA_IRQ_IOC_MASK))) {
			TxCallBack(TxRingPtr);
		}
	}

	/*****************************************************************************/
		/*
		*
		* This is the DMA RX callback function called by the RX interrupt handler.
		* This function handles finished BDs by hardware, attaches new buffers to those
		* BDs, and give them back to hardware to receive more incoming packets
		*
		* @param	RxRingPtr is a pointer to RX channel of the DMA engine.
		*
		* @return	None.
		*
		* @note		None.
		*
	******************************************************************************/
	static void RxCallBack(XAxiDma_BdRing * RxRingPtr)
	{
		int BdCount;
		XAxiDma_Bd *BdPtr;
		XAxiDma_Bd *BdCurPtr;
		u32 BdSts;
		int Index;

		/* Get finished BDs from hardware */
		BdCount = XAxiDma_BdRingFromHw(RxRingPtr, 1, &BdPtr);
		//xil_printf("Rx Count %d\r\n", BdCount);
		//while (!BdCount) {
			//xil_printf("Rx interrupt, but not bd!\r\n");
			//BdCount = XAxiDma_BdRingFromHw(RxRingPtr, 1, &BdPtr);
		//}

		BdCurPtr = BdPtr;
		for (Index = 0; Index < BdCount; Index++) {
			/*
			* Check the flags set by the hardware for status
			* If error happens, processing stops, because the DMA engine
			* is halted after this BD.
			*/
			xil_printf("\nENTERED CALLBACK");
			BdSts = XAxiDma_BdGetSts(BdCurPtr);
			if ((BdSts & XAXIDMA_BD_STS_ALL_ERR_MASK) ||
				(!(BdSts & XAXIDMA_BD_STS_COMPLETE_MASK))) {
				Error = 1;
				break;
			}
			/* Find the next processed BD */
			BdCurPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(RxRingPtr, BdCurPtr);
			RxDone += 1;
		}

		/* Free all processed BDs for future transmission */
		if (XAxiDma_BdRingFree(RxRingPtr, BdCount, BdPtr) != XST_SUCCESS) {
			Error = 1;
		}

	}

	/*****************************************************************************/
		/*
		*
		* This is the DMA RX interrupt handler function
		*
		* It gets the interrupt status from the hardware, acknowledges it, and if any
		* error happens, it resets the hardware. Otherwise, if a completion interrupt
		* presents, then it calls the callback function.
		*
		* @param	Callback is a pointer to RX channel of the DMA engine.
		*
		* @return	None.
		*
		* @note		None.
		*
	******************************************************************************/
	static void RxIntrHandler(void *Callback)
	{
		XAxiDma_BdRing *RxRingPtr = (XAxiDma_BdRing *) Callback;
		u32 IrqStatus;
		int TimeOut;

		/* Read pending interrupts */
		IrqStatus = XAxiDma_BdRingGetIrq(RxRingPtr);

		/* Acknowledge pending interrupts */
		XAxiDma_BdRingAckIrq(RxRingPtr, IrqStatus);

		/*
		* If no interrupt is asserted, we do not do anything
		*/
		if (!(IrqStatus & XAXIDMA_IRQ_ALL_MASK)) {
			return;
		}

		/*
		* If error interrupt is asserted, raise error flag, reset the
		* hardware to recover from the error, and return with no further
		* processing.
		*/
		if ((IrqStatus & XAXIDMA_IRQ_ERROR_MASK)) {
			XAxiDma_BdRingDumpRegs(RxRingPtr);
			Error = 1;
			/* Reset could fail and hang
			* NEED a way to handle this or do not call it??
			*/
			XAxiDma_Reset(&AxiDma);
			TimeOut = RESET_TIMEOUT_COUNTER;
			while (TimeOut) {
				if(XAxiDma_ResetIsDone(&AxiDma)) {
					break;
				}
				TimeOut -= 1;
			}

			return;
		}

		/*
		* If completion interrupt is asserted, call RX call back function
		* to handle the processed BDs and then raise the according flag.
		*/
		if ((IrqStatus & (XAXIDMA_IRQ_DELAY_MASK | XAXIDMA_IRQ_IOC_MASK))) {
			RxCallBack(RxRingPtr);
		}
	}

	/*****************************************************************************/
		/*
		*
		* This function setups the interrupt system so interrupts can occur for the
		* DMA, it assumes INTC component exists in the hardware system.
		*
		* @param	IntcInstancePtr is a pointer to the instance of the INTC.
		* @param	AxiDmaPtr is a pointer to the instance of the DMA engine
		* @param	TxIntrId is the TX channel Interrupt ID.
		* @param	RxIntrId is the RX channel Interrupt ID.
		*
		* @return
		*		- XST_SUCCESS if successful,
		*		- XST_FAILURE.if not succesful
		*
		* @note		None.
		*
	******************************************************************************/
	static int SetupIntrSystem(INTC * IntcInstancePtr,
				XAxiDma * AxiDmaPtr, u16 TxIntrId, u16 RxIntrId)
	{
		XAxiDma_BdRing *TxRingPtr = XAxiDma_GetTxRing(AxiDmaPtr);
		XAxiDma_BdRing *RxRingPtr = XAxiDma_GetRxRing(AxiDmaPtr);
		int Status;

		#ifdef XPAR_INTC_0_DEVICE_ID

			/* Initialize the interrupt controller and connect the ISRs */
			Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
			if (Status != XST_SUCCESS) {

				xil_printf("Failed init intc\r\n");
				return XST_FAILURE;
			}

			Status = XIntc_Connect(IntcInstancePtr, TxIntrId,
						(XInterruptHandler) TxIntrHandler, TxRingPtr);
			if (Status != XST_SUCCESS) {

				xil_printf("Failed tx connect intc\r\n");
				return XST_FAILURE;
			}

			Status = XIntc_Connect(IntcInstancePtr, RxIntrId,
						(XInterruptHandler) RxIntrHandler, RxRingPtr);
			if (Status != XST_SUCCESS) {

				xil_printf("Failed rx connect intc\r\n");
				return XST_FAILURE;
			}

			/* Start the interrupt controller */
			Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
			if (Status != XST_SUCCESS) {

				xil_printf("Failed to start intc\r\n");
				return XST_FAILURE;
			}

			XIntc_Enable(IntcInstancePtr, TxIntrId);
			XIntc_Enable(IntcInstancePtr, RxIntrId);

		#else

			XScuGic_Config *IntcConfig;

			/*
			* Initialize the interrupt controller driver so that it is ready to
			* use.
			*/
			IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
			if (NULL == IntcConfig) {
				return XST_FAILURE;
			}

			Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
							IntcConfig->CpuBaseAddress);
			if (Status != XST_SUCCESS) {
				return XST_FAILURE;
			}


			XScuGic_SetPriorityTriggerType(IntcInstancePtr, TxIntrId, 0xA0, 0x3);
			XScuGic_SetPriorityTriggerType(IntcInstancePtr, RxIntrId, 0xA0, 0x3);
			/*
			* Connect the device driver handler that will be called when an
			* interrupt for the device occurs, the handler defined above performs
			* the specific interrupt processing for the device.
			*/
			Status = XScuGic_Connect(IntcInstancePtr, TxIntrId,
						(Xil_InterruptHandler)TxIntrHandler,
						TxRingPtr);
			if (Status != XST_SUCCESS) {
				return Status;
			}

			Status = XScuGic_Connect(IntcInstancePtr, RxIntrId,
						(Xil_InterruptHandler)RxIntrHandler,
						RxRingPtr);
			if (Status != XST_SUCCESS) {
				return Status;
			}

			XScuGic_Enable(IntcInstancePtr, TxIntrId);
			XScuGic_Enable(IntcInstancePtr, RxIntrId);
		#endif

			/* Enable interrupts from the hardware */

			Xil_ExceptionInit();
			Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
					(Xil_ExceptionHandler)INTC_HANDLER,
					(void *)IntcInstancePtr);

			Xil_ExceptionEnable();

			return XST_SUCCESS;
		}

	/*****************************************************************************/
		/**
		*
		* This function disables the interrupts for DMA engine.
		*
		* @param	IntcInstancePtr is the pointer to the INTC component instance
		* @param	TxIntrId is interrupt ID associated w/ DMA TX channel
		* @param	RxIntrId is interrupt ID associated w/ DMA RX channel
		*
		* @return	None.
		*
		* @note		None.
		*
	******************************************************************************/
	static void DisableIntrSystem(INTC * IntcInstancePtr,
						u16 TxIntrId, u16 RxIntrId)
	{
		#ifdef XPAR_INTC_0_DEVICE_ID
			/* Disconnect the interrupts for the DMA TX and RX channels */
			XIntc_Disconnect(IntcInstancePtr, TxIntrId);
			XIntc_Disconnect(IntcInstancePtr, RxIntrId);
		#else
			XScuGic_Disconnect(IntcInstancePtr, TxIntrId);

			XScuGic_Disconnect(IntcInstancePtr, RxIntrId);
		#endif
		}

	/*****************************************************************************/
		/*
		*
		* This function sets up the TX channel of a DMA engine to be ready for packet
		* transmission.
		*
		* @param	AxiDmaInstPtr is the pointer to the instance of the DMA engine.
		*
		* @return	- XST_SUCCESS if the setup is successful.
		*		- XST_FAILURE otherwise.
		*
		* @note		None.
		*
	******************************************************************************/
	static int TxSetup(XAxiDma * AxiDmaInstPtr)
	{
		XAxiDma_BdRing *TxRingPtr = XAxiDma_GetTxRing(&AxiDma);
		XAxiDma_Bd BdTemplate;
		int Status;

		/* Disable all TX interrupts before TxBD space setup */
		XAxiDma_BdRingIntDisable(TxRingPtr, XAXIDMA_IRQ_ALL_MASK);

		/* Setup TxBD space  */
		Status = XAxiDma_BdRingCreate(TxRingPtr, TX_BD_SPACE_BASE,
						TX_BD_SPACE_BASE,
						XAXIDMA_BD_MINIMUM_ALIGNMENT, TX_BD_COUNT);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed create BD ring\r\n");
			return XST_FAILURE;
		}

		/*
		* Like the RxBD space, we create a template and set all BDs to be the
		* same as the template. The sender has to set up the BDs as needed.
		*/
		XAxiDma_BdClear(&BdTemplate);
		Status = XAxiDma_BdRingClone(TxRingPtr, &BdTemplate);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed clone BDs\r\n");
			return XST_FAILURE;
		}

		/*
		* Set the coalescing threshold
		*/
		Status = XAxiDma_BdRingSetCoalesce(TxRingPtr, COALESCING_COUNT,
				DELAY_TIMER_COUNT);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed set coalescing"
			" %d/%d\r\n",COALESCING_COUNT, DELAY_TIMER_COUNT);
			return XST_FAILURE;
		}

		/* Enable all TX interrupts */
		XAxiDma_BdRingIntEnable(TxRingPtr, XAXIDMA_IRQ_ALL_MASK);

		/* Start the TX channel */
		Status = XAxiDma_BdRingStart(TxRingPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed bd start\r\n");
			return XST_FAILURE;
		}

		return XST_SUCCESS;
	}

	/*****************************************************************************/
		/*
		*
		* This function sets up RX channel of the DMA engine to be ready for packet
		* reception
		*
		* @param	AxiDmaInstPtr is the pointer to the instance of the DMA engine.
		*
		* @return	- XST_SUCCESS if the setup is successful.
		*		- XST_FAILURE if fails.
		*
		* @note		None.
		*
	******************************************************************************/
	static int RxSetup(XAxiDma * AxiDmaInstPtr)
	{
		XAxiDma_BdRing *RxRingPtr;
		int Status;
		XAxiDma_Bd BdTemplate;

		RxRingPtr = XAxiDma_GetRxRing(&AxiDma);

		/* Disable all RX interrupts before RxBD space setup */
		XAxiDma_BdRingIntDisable(RxRingPtr, XAXIDMA_IRQ_ALL_MASK);

		/* Setup Rx BD space */
		Status = XAxiDma_BdRingCreate(RxRingPtr, RX_BD_SPACE_BASE,
						RX_BD_SPACE_BASE,
						XAXIDMA_BD_MINIMUM_ALIGNMENT, RX_BD_COUNT);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx bd create failed with %d\r\n", Status);
			return XST_FAILURE;
		}

		/*
		* Setup a BD template for the Rx channel. Then copy it to every RX BD.
		*/
		XAxiDma_BdClear(&BdTemplate);
		Status = XAxiDma_BdRingClone(RxRingPtr, &BdTemplate);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx bd clone failed with %d\r\n", Status);
			return XST_FAILURE;
		}

		/*
		* Set the coalescing threshold, so only one receive interrupt
		* occurs for this example
		*
		* If you would like to have multiple interrupts to happen, change
		* the COALESCING_COUNT to be a smaller value
		*/
		Status = XAxiDma_BdRingSetCoalesce(RxRingPtr, 1,
				DELAY_TIMER_COUNT);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx set coalesce failed with %d\r\n", Status);
			return XST_FAILURE;
		}

		/* Enable all RX interrupts */
		XAxiDma_BdRingIntEnable(RxRingPtr, XAXIDMA_IRQ_ALL_MASK);

		/* Start RX DMA channel */
		Status = XAxiDma_BdRingStart(RxRingPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx start BD ring failed with %d\r\n", Status);
			return XST_FAILURE;
		}

		return XST_SUCCESS;
	}

	/*****************************************************************************/
		/*
		*
		* This asks the PL to send a data.
		*
		* @param	AxiDmaInstPtr points to the DMA engine instance
		*
		* @return
		* 		- XST_SUCCESS if the DMA accepts all the packets successfully,
		* 		- XST_FAILURE if error occurs
		*
	******************************************************************************/
	static int SendRxBd(XAxiDma * AxiDmaInstPtr) {
		XAxiDma_BdRing *RxRingPtr;
		int Status;
		XAxiDma_Bd *BdPtr;
		XAxiDma_Bd *BdCurPtr;
		UINTPTR RxBufferPtr;

		RxRingPtr = XAxiDma_GetRxRing(&AxiDma);

		/* Attach buffers to RxBD ring so we are ready to receive packets */
		Status = XAxiDma_BdRingAlloc(RxRingPtr, RX_BD_COUNT, &BdPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx bd alloc failed %d\r\n", Status);
			return XST_FAILURE;
		}

		BdCurPtr = BdPtr;
		RxBufferPtr = RX_BUFFER_BASE;

		Status = XAxiDma_BdSetBufAddr(BdCurPtr, RxBufferPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx set buffer failed %d\r\n", Status);
			return XST_FAILURE;
		}
		Status = XAxiDma_BdSetLength(BdCurPtr, RX_BD_LEN,
					RxRingPtr->MaxTransferLen);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx set length failed %d\r\n", Status);
			return XST_FAILURE;
		}

		/* Hint: Receive BDs do not need to set anything for the control
		* The hardware will set the SOF/EOF bits per stream status
		*/
		XAxiDma_BdSetCtrl(BdCurPtr, 0);
		XAxiDma_BdSetId(BdCurPtr, RxBufferPtr);

		Status = XAxiDma_BdRingToHw(RxRingPtr, RX_BD_COUNT, BdPtr);
		if (Status != XST_SUCCESS) {
			xil_printf("Rx ToHw failed with %d\r\n", Status);
			return XST_FAILURE;
		}
		return XST_SUCCESS;
	}

/* ACCELERATOR FUNCTIONS */
	/*****************************************************************************/
		/*
		* Shiming:
		* This function is for sending consecutive data (length specified with macro).
		*
		* @param	AxiDmaInstPtr points to the DMA engine instance
		* @param	BufferBaseAddr base address of the buffer to use
		* @param	PadZeroNum number of zeroes to pad
		*
		* @return
		* 		- XST_SUCCESS if the DMA accepts all the packets successfully,
		* 		- XST_FAILURE if error occurs
		*
		* @note		In case the number of data is not enough (ACC_VEC_LEN),
		* 				you can set PadZeroNum so the function adds an additional bd
		* 				which points to the zero buffer.
		*
	******************************************************************************/
	static int SendConsecutivePacket(XAxiDma * AxiDmaInstPtr, \
			UINTPTR BufferBaseAddr, int PadZeroNum)
	{
		XAxiDma_BdRing *TxRingPtr = XAxiDma_GetTxRing(AxiDmaInstPtr);
		u8 *TxDataPtr;
		XAxiDma_Bd *BdPtr, *BdCurPtr;
		int Status;
		int BdCount;
		UINTPTR BufferCurAddr;
		u32 CrBits = 0;
		u32 PadLength = PadZeroNum * ACC_DATA_SIZE;

		if (PadZeroNum > ACC_VEC_LEN || PadZeroNum < 0) {
			xil_printf("Invalid PadZeroNum parameter %d. "
					"Max is vector length %d\r\n", PadZeroNum, ACC_VEC_LEN);
			return XST_INVALID_PARAM;
		}

		/*
		* Each packet is limited to TxRingPtr->MaxTransferLen
		*
		* This will not be the case if hardware has store and forward built in
		*/
		if (CONSECUTIVE_DATA_BD_LEN > TxRingPtr->MaxTransferLen) {
			xil_printf("Invalid total per packet transfer length for the "
					"packet %d/%d\r\n",
					CONSECUTIVE_DATA_BD_LEN, TxRingPtr->MaxTransferLen);
			return XST_INVALID_PARAM;
		}

		BdCount = ((PadZeroNum > 0) ? CONSECUTIVE_DATA_BD_COUNT + 1	: CONSECUTIVE_DATA_BD_COUNT);

		/* Flush the SrcBuffer before the DMA transfer, in case the Data Cache
		* is enabled
		*/
		TxDataPtr = (u8 *)BufferBaseAddr;	// Need this for flushing DCache

		/** Shiming:
		 * I manually force the PS to flush cache starting from TxDataPtr.
		 */
		Xil_DCacheFlushRange((UINTPTR)TxDataPtr, \
				CONSECUTIVE_DATA_BD_LEN - PadZeroNum * ACC_DATA_SIZE);
		#ifdef __aarch64__
			Xil_DCacheFlushRange((UINTPTR)RX_BUFFER_BASE, \
					CONSECUTIVE_DATA_BD_LEN - PadZeroNum * ACC_DATA_SIZE);
		#endif
			Status = XAxiDma_BdRingAlloc(TxRingPtr, BdCount, &BdPtr);
			if (Status != XST_SUCCESS) {
				xil_printf("Failed bd alloc\r\n");
				return XST_FAILURE;
			}

			/*
			* Set up the BD using the information of the packet to transmit
			* Each transfer has NUMBER_OF_BDS_PER_PKT BDs
			*/

			BdCurPtr = BdPtr;
			BufferCurAddr = BufferBaseAddr;

			Status = XAxiDma_BdSetBufAddr(BdCurPtr, BufferCurAddr);
			if (Status != XST_SUCCESS) {
				xil_printf("Tx set buffer addr %x on BD %x failed %d\r\n",
				(unsigned int)BufferCurAddr, (UINTPTR)BdCurPtr, Status);
				return XST_FAILURE;
			}
			Status = XAxiDma_BdSetLength(BdCurPtr, \
					CONSECUTIVE_DATA_BD_LEN - PadLength, \
					TxRingPtr->MaxTransferLen);
			if (Status != XST_SUCCESS) {
				xil_printf("Tx set length on BD %x failed %d\r\n", \
						(UINTPTR)BdCurPtr, Status);
				return XST_FAILURE;
			}
			/* The first BD has SOF set */
			CrBits |= XAXIDMA_BD_CTRL_TXSOF_MASK;
		#if (XPAR_AXIDMA_0_SG_INCLUDE_STSCNTRL_STRM == 1)
				/* The first BD has total transfer length set
				* in the last APP word, this is for the
				* loopback widget
				*/
				Status = XAxiDma_BdSetAppWord(BdCurPtr,
					XAXIDMA_LAST_APPWORD,
					CONSECUTIVE_DATA_BD_LEN);
					if (Status != XST_SUCCESS) {
					xil_printf("Set app word failed with %d\r\n",
					Status);
				}
		#endif
			if (PadZeroNum > 0) {
				/* Finish current Bd setting */
				XAxiDma_BdSetCtrl(BdCurPtr, CrBits);
				XAxiDma_BdSetId(BdCurPtr, BufferCurAddr);

				/* Set another bd full of 0 */
				BdCurPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(TxRingPtr, BdCurPtr);
				BufferCurAddr = (UINTPTR)ZeroBuffer;

				Status = XAxiDma_BdSetBufAddr(BdCurPtr, BufferCurAddr);
				if (Status != XST_SUCCESS) {
					xil_printf("Tx set zero buffer on BD %x failed %d\r\n",
					(UINTPTR)BdCurPtr, Status);
					return XST_FAILURE;
				}
				Status = XAxiDma_BdSetLength(BdCurPtr, PadLength, \
						TxRingPtr->MaxTransferLen);
				if (Status != XST_SUCCESS) {
					xil_printf("Tx set length on BD %x failed %d\r\n", \
							(UINTPTR)BdCurPtr, Status);
					return XST_FAILURE;
				}
				/* Set EOF on this bd  */
				CrBits = 0 | XAXIDMA_BD_CTRL_TXEOF_MASK;
				XAxiDma_BdSetCtrl(BdCurPtr, CrBits);
				XAxiDma_BdSetId(BdCurPtr, BufferCurAddr);
			} else {
				/* Set both SOF and EOF on this bd */
				CrBits |= XAXIDMA_BD_CTRL_TXEOF_MASK;
				XAxiDma_BdSetCtrl(BdCurPtr, CrBits);
				XAxiDma_BdSetId(BdCurPtr, BufferCurAddr);
			}

			/* Give the BD(s) to hardware */
			Status = XAxiDma_BdRingToHw(TxRingPtr, BdCount, BdPtr);
			if (Status != XST_SUCCESS) {
				xil_printf("Failed to send to hw, failure %d\r\n", Status);
				return XST_FAILURE;
			}

			return XST_SUCCESS;
	}

	/*****************************************************************************/
		/*
		* Shiming:
		* This function is for sending scattered data with fixed interval.
		*
		* @param	AxiDmaInstPtr points to the DMA engine instance
		* @param	BufferBaseAddr base address of the buffer to use
		* @param	PadZeroNum number of zeroes to pad
		* @param	ScatterInterval the interval of scattered data
		*
		* @return
		* 		- XST_SUCCESS if the DMA accepts all the packets successfully,
		* 		- XST_FAILURE if error occurs
		*
		* @note		This function is designed for the scenario where a column in
		* 				a 2d array is to be sent.
		* 			The length of data is determined in the macros.
		*
	******************************************************************************/
	static int SendScatteredPacket(XAxiDma * AxiDmaInstPtr, \
			UINTPTR BufferBaseAddr, int PadZeroNum, int ScatterInterval)
	{
		XAxiDma_BdRing *TxRingPtr = XAxiDma_GetTxRing(AxiDmaInstPtr);
		u8 *TxDataPtr;
		XAxiDma_Bd *BdPtr, *BdCurPtr;
		int Status;
		int BdCount;
		int Index;
		UINTPTR BufferCurAddr;
		u32 CrBits = 0;
		u32 PadLength = PadZeroNum * ACC_DATA_SIZE;
		u32 LengthToSet;

		if (PadZeroNum > ACC_VEC_LEN || PadZeroNum < 0) {
			xil_printf("Invalid PadZeroNum parameter %d. "
						"Max is vector length %d\r\n",
						PadZeroNum, ACC_VEC_LEN);
					return XST_INVALID_PARAM;
		}

		/*
		* Each packet is limited to TxRingPtr->MaxTransferLen
		*
		* This will not be the case if hardware has store and forward built in
		*/
		if (PadLength > TxRingPtr->MaxTransferLen) {
			xil_printf("Invalid total per packet transfer length for the "
				"packet %d/%d\r\n",
				PadLength, TxRingPtr->MaxTransferLen);
			return XST_INVALID_PARAM;
		}

		BdCount = ((PadZeroNum > 0) ? SCATTERED_DATA_BD_COUNT - PadZeroNum + 1\
				: SCATTERED_DATA_BD_COUNT);

		/* Flush the SrcBuffer before the DMA transfer, in case the Data Cache
		* is enabled
		*/
		TxDataPtr = (u8 *)BufferBaseAddr;	// Need this for flushing DCache

		for (Index = 0; Index < SCATTERED_DATA_BD_COUNT - PadZeroNum; ++Index) {
			Xil_DCacheFlushRange((UINTPTR)TxDataPtr, ACC_DATA_SIZE);
			TxDataPtr += ScatterInterval * ACC_DATA_SIZE;
		#ifdef __aarch64__
				Xil_DCacheFlushRange((UINTPTR)RX_BUFFER_BASE \
						+ Index * ScatterInterval * ACC_DATA_SIZE, ACC_DATA_SIZE);
		#endif
			}

			Status = XAxiDma_BdRingAlloc(TxRingPtr, BdCount, &BdPtr);
			if (Status != XST_SUCCESS) {
				xil_printf("Failed bd alloc\r\n");
				return XST_FAILURE;
			}

			/*
			* Set up the BD using the information of the packet to transmit
			* Each transfer has NUMBER_OF_BDS_PER_PKT BDs
			*/
			BdCurPtr = BdPtr;
			BufferCurAddr = BufferBaseAddr;
			LengthToSet = ACC_DATA_SIZE;
			for(Index = 0; Index < BdCount; Index++) {
				if (Index == BdCount - 1 && PadZeroNum > 0) {
					BufferCurAddr = (UINTPTR)ZeroBuffer;
					LengthToSet = PadLength;
				}
				xil_printf("An int to send: %u at %p, in bd: %p \r\n",
						*((u32 *)BufferCurAddr), (u32 *)BufferCurAddr, BdCurPtr);
				Status = XAxiDma_BdSetBufAddr(BdCurPtr, BufferCurAddr);
				if (Status != XST_SUCCESS) {
					xil_printf("Tx set buffer addr %x on BD %x failed %d\r\n",
					(unsigned int)BufferCurAddr, (UINTPTR)BdCurPtr, Status);
					return XST_FAILURE;
				}
				Status = XAxiDma_BdSetLength(BdCurPtr, LengthToSet, \
						TxRingPtr->MaxTransferLen);
				if (Status != XST_SUCCESS) {
					xil_printf("Tx set length on BD %x failed %d\r\n", \
							(UINTPTR)BdCurPtr, Status);
					return XST_FAILURE;
				}
				if (Index == 0) {
					CrBits |= XAXIDMA_BD_CTRL_TXSOF_MASK;
		#if (XPAR_AXIDMA_0_SG_INCLUDE_STSCNTRL_STRM == 1)
					/* The first BD has total transfer length set
					* in the last APP word, this is for the
					* loopback widget
					*/
					Status = XAxiDma_BdSetAppWord(BdCurPtr,
						XAXIDMA_LAST_APPWORD,
						ACC_DATA_SIZE);
						if (Status != XST_SUCCESS) {
						xil_printf("Set app word failed with %d\r\n",
						Status);
					}
		#endif
				}
				if (Index == BdCount - 1) {
					CrBits |= XAXIDMA_BD_CTRL_TXEOF_MASK;
				}
				XAxiDma_BdSetCtrl(BdCurPtr, CrBits);
				XAxiDma_BdSetId(BdCurPtr, BufferCurAddr);
				BufferCurAddr += ACC_DATA_SIZE * (ScatterInterval + 1);
				BdCurPtr = (XAxiDma_Bd *)XAxiDma_BdRingNext(TxRingPtr, BdCurPtr);
			}

			/* Give the BD(s) to hardware */
			Status = XAxiDma_BdRingToHw(TxRingPtr, BdCount,
								BdPtr);
			if (Status != XST_SUCCESS) {
				xil_printf("Failed to send to hw, failure %d\r\n", Status);
				return XST_FAILURE;
			}

			return XST_SUCCESS;
	}

	/*****************************************************************************/
		/*
		*
		* This is an example function of one calculation on PL (think of the one you
		*  made in Lab 2).
		* This is heavily modified and I do not guarantee it compiles (e.g. some vars
		*  may be missing). This is just to show you the procedure of how it transmits 2
		*  slices of arrays onto the accelerator, and then asks it to start, and then
		*  configure a receiving BD so as to receive result from the accelerator.
		*
		* @param someArray The example array.
		*
		* @return
		* 		- 1 No meaning. Just an example
		*
	******************************************************************************/
	static int multiplyVectors(int* input, int* weights){
		//xil_printf("\nENTERING CALCULATE VECTOR");
		int Status;
		int BdCount;		// Number of bds to wait for

		int PadZeroNum = 0;	// Number of 0s to pad, if a vector is too short for the accelerator. Here 0 is just for example

		/*
		 * Load the slices in an image and do all related calculations
		 * */
		BdCount = ((PadZeroNum > 0) ? CONSECUTIVE_DATA_BD_COUNT + 1 : CONSECUTIVE_DATA_BD_COUNT);
		/** Transmit slice A */
		AccWriteSelA();
    	int slv_reg0_rdata = Xil_In32(AXI4L_SLV_REG_0_ADDR);
    	//xil_printf("\nAAA TEST SEE IF IT SAVES THE 0 %d", slv_reg0_rdata);
		//xil_printf("\nENABLING TRANSMISSION OF WEIGHTS");
		Status = SendConsecutivePacket(&AxiDma,
						(UINTPTR)(weights), PadZeroNum);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed send packet\r\n");
			return -1;
		}
		while (TxDone < BdCount && !Error) {
			/* NOP */
			//xil_printf("\nWaiting for TxDone: %d", TxDone);
		}
		TxDone = 0;
		/** Transmit slice B */
		//xil_printf("\nENABLING TRANSMISSION OF INPUT");
		AccWriteSelB();
    	slv_reg0_rdata = Xil_In32(AXI4L_SLV_REG_0_ADDR);

    	//xil_printf("\nAAA TEST SEE IF IT SAVES THE 1 %d", slv_reg0_rdata);

		Status = SendConsecutivePacket(&AxiDma,
			(UINTPTR)(input), PadZeroNum);
		if (Status != XST_SUCCESS) {
			xil_printf("Failed send packet\r\n");
			return -1;

		}


		while (TxDone < BdCount  && !Error) {
			/** Wait for transmission configuration to finish. */
			/** Here the processor does nothing. Try not to use this and find a better way to schedule the work! */
			/* NOP */
		}
		TxDone = 0;
    	int temp_written_result = Xil_In32(AXI4L_SLV_REG_2_ADDR);
    	//xil_printf("\nCHECK IF THE VALUE IS RESTORED  should be 0 or 1 if previously run %d", temp_written_result);


		AccWriteValidValue();
		AccWriteStop();
    	temp_written_result = Xil_In32(AXI4L_SLV_REG_2_ADDR);
    	//xil_printf("\nCHECK IF THE VALUE IS RESTORED  should be 0 %d", temp_written_result);
		/** Let the accelerator start its work */
		//xil_printf("\nSTARTING ACCELERATOR");
		AccWriteStart();
    	slv_reg0_rdata = Xil_In32(AXI4L_SLV_REG_0_ADDR);
    	//xil_printf("\nAAA TEST SEE IF IT SAVES THE 2 %d\n", slv_reg0_rdata);
		AccWriteStop();
		/** WAIT UNTIL ACCELERATOR FINISHES */
		while (1) {
	    	temp_written_result = Xil_In32(AXI4L_SLV_REG_2_ADDR);
	    	if(temp_written_result)
	    		break;

		}
    	slv_reg0_rdata = Xil_In32(AXI4L_SLV_REG_1_ADDR);
		if (Error) {
			xil_printf("Error in bds...\r\n");
			return -1;
		}

		return slv_reg0_rdata;
	}


	/*****************************************************************************/
		/*
		*
		* Uart16550 setup routine, need to set baudrate to 9600 and data bits to 8
		*
		* @param	None
		*
		* @return	None
		*
		* @note		None.
		*
	******************************************************************************/
	#ifdef XPAR_UARTNS550_0_BASEADDR
	static void Uart550_Setup(void)
	{

		XUartNs550_SetBaud(XPAR_UARTNS550_0_BASEADDR,
				XPAR_XUARTNS550_CLOCK_HZ, 9600);

		XUartNs550_SetLineControlReg(XPAR_UARTNS550_0_BASEADDR,
				XUN_LCR_8_DATA_BITS);
	}
	#endif
