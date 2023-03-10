
/*****************************************************************************/
/**
 *
 * @file main.c
 *
 * Modified by Chen & Rodrigo
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

	#include "xmult_accel_core_call.h"

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
	#define ACC_VEC_LEN 32
	#define	ARRAYSIZE(x)	(sizeof(x) / sizeof(x[ 0 ]))

	#define SCATTERED_DATA_BD_COUNT ACC_VEC_LEN
	#define SCATTERED_DATA_BD_LEN ACC_DATA_SIZE
	#define CONSECUTIVE_DATA_BD_COUNT 1
	#define CONSECUTIVE_DATA_BD_LEN (ACC_VEC_LEN * ACC_DATA_SIZE)
	#define TX_BD_COUNT SCATTERED_DATA_BD_COUNT

	#define RX_BD_COUNT 1
	#define RX_BD_LEN ACC_DATA_SIZE


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

/************************** Function Prototypes ******************************/
	#ifdef XPAR_UARTNS550_0_BASEADDR
	static void Uart550_Setup(void);
	#endif


	static int init_dma(XAxiDma *axiDmaPtr);
	static void networkPSrun();
	static int Setup_HW_Accelerator();

/************************** Variable Definitions *****************************/
	/*
	* Device instance definitions
	*/
	XAxiDma AxiDma;

    static unsigned int dma_size = 784 * sizeof(float);
	static unsigned int dma_out_size = 1 * sizeof(float);

/*****************************************************************************/

/**
*
* Main function
*
* @param	None
*
* @return
*		- XST_SUCCESS if tests pass
*		- XST_FAILURE if fails.
* @note		None.
*
******************************************************************************/
int main(void)
{
		int Status;

		/* Initial setup for Uart16550 */
	#ifdef XPAR_UARTNS550_0_BASEADDR
		Uart550_Setup();
	#endif

		xil_printf("\r\n--- Entering main() --- \r\n");
	#ifdef __aarch64__
		Xil_SetTlbAttributes(TX_BD_SPACE_BASE, MARK_UNCACHEABLE);
		Xil_SetTlbAttributes(RX_BD_SPACE_BASE, MARK_UNCACHEABLE);
	#endif

	    /* DMA setup */
		Status = init_dma(&AxiDma);
        if (Status != XST_SUCCESS) {
           exit(-1);
        }

	/* True start of the network */
	networkPSrun();

	xil_printf("--- Exiting main() --- \r\n");
	return XST_SUCCESS;
}

#ifdef XPAR_UARTNS550_0_BASEADDR
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
static void Uart550_Setup(void)
{

	XUartNs550_SetBaud(XPAR_UARTNS550_0_BASEADDR,
			XPAR_XUARTNS550_CLOCK_HZ, 9600);

	XUartNs550_SetLineControlReg(XPAR_UARTNS550_0_BASEADDR,
			XUN_LCR_8_DATA_BITS);
}
#endif

/*****************************************************************************/
/* A function that wraps all AXI DMA initialization related API calls
 *
 * @param       None
 *
 * @return
 * 		- XST_SUCCESS if tests pass
 * 		- XST_FAILURE if fails.
 *
 * @note		None.
 *
******************************************************************************/
static int init_dma(XAxiDma *axiDmaPtr)
{
   XAxiDma_Config *CfgPtr;
   int status;
   // Get pointer to DMA configuration
   CfgPtr = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
   if(!CfgPtr){
      print("Error looking for AXI DMA config\n\r");
      return XST_FAILURE;
   }
   // Initialize the DMA handle
   status = XAxiDma_CfgInitialize(axiDmaPtr,CfgPtr);
   if(status != XST_SUCCESS){
      print("Error initializing DMA\n\r");
      return XST_FAILURE;
   }
   // Check for scatter gather mode - must have simple mode only
   if(XAxiDma_HasSg(axiDmaPtr)){
      print("Error DMA configured in SG mode\n\r");
      return XST_FAILURE;
   }
   //disable the interrupts
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DEVICE_TO_DMA);
   XAxiDma_IntrDisable(axiDmaPtr, XAXIDMA_IRQ_ALL_MASK,XAXIDMA_DMA_TO_DEVICE);

   return XST_SUCCESS;
}


/***************************** AXIS Part *************************************/
XMult_accel_core_call xmult_dev;

XMult_accel_core_call_Config xmmult_config = {
	0,
	XPAR_MULT_ACCEL_CORE_CALL_0_S_AXI_CONTROL_BUS_BASEADDR
};

static void XMmultStart(void *InstancePtr){
	XMult_accel_core_call *pExample = (XMult_accel_core_call *)InstancePtr;
	/* Disable the local interrupt */
	XMult_accel_core_call_InterruptDisable(pExample,1);
	/* Disable the global interrupt */
	XMult_accel_core_call_InterruptGlobalDisable(pExample);
	XMult_accel_core_call_Start(pExample);
}

/* Setup the Vivado HLS Block */
static int Setup_HW_Accelerator()
{
	/* Set up XMult */
	int status = XMult_accel_core_call_Initialize(&xmult_dev,0);
	if(status != XST_SUCCESS){
		xil_printf("Error: example setup failed\n");
		return XST_FAILURE;
	}
	XMmultStart(&xmult_dev);

	return 0;
}

/* HW accelerator */
static int Accelerator_call(float* vector_A, float* vector_B, float* out) 
{
	Setup_HW_Accelerator();
	/* Flush the cache */
	Xil_DCacheFlushRange((unsigned int)vector_A, dma_size);
	Xil_DCacheFlushRange((unsigned int)vector_B, dma_size);
	Xil_DCacheFlushRange((unsigned int)out, dma_out_size);

	/* Transfer vector_A to the Vivado HLS block */
	int status = XAxiDma_SimpleTransfer(&AxiDma, (unsigned int) vector_A, dma_size, XAXIDMA_DMA_TO_DEVICE);
	if (status != XST_SUCCESS) {
		xil_printf("Error: DMA transfer to Vivado HLS block failed(vector_A): %d\n", status);
		return XST_FAILURE;
	}
	/* Wait for transfer to be done */
	while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE)) {
		/* Wait */
	};

	/* Transfer vector_B to the Vivado HLS block */
	status = XAxiDma_SimpleTransfer(&AxiDma, (unsigned int) vector_B, dma_size, XAXIDMA_DMA_TO_DEVICE);
	if (status != XST_SUCCESS) {
		xil_printf("Error: DMA transfer to Vivado HLS block failed(vector_B): %d\n", status);
		return XST_FAILURE;
	}
	/* Wait for transfer to be done */
	while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE)) {
		/* Wait */
	};

	/* Get results from the Vivado HLS block */
	status = XAxiDma_SimpleTransfer(&AxiDma, (unsigned int) out, dma_size, XAXIDMA_DEVICE_TO_DMA);
	if (status != XST_SUCCESS) {
		xil_printf("Error: DMA transfer from Vivado HLS block failed(out): %d\n", status);
		return XST_FAILURE;
	}
	/* Wait for transfer to be done */
	while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE)) {
		/* Wait */
	} ;

	/* Poll the DMA engine to verify transfers are complete */
	while ((XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA)) || (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE))) ;
	
	return 0;
}

/****************************** NN Part **************************************/
/* Argmax function: return the index of the largest element in the array */
static int networkPSargmax(float* result){
	int max_index = 0;
	for (int i = 0; i < 10; i++)
		if (result[i] > result[max_index])
			max_index = i;
	return max_index;
}

/* Sigma function: 1/(1+e^-z) */
static float networkPSsigmoid(float z){
	return 1.0/(1.0 + exp(-z));
}

/* Software feedforward */
// size_of_input = 784, size_of_result = 30
static void networkPSfeedforward(float* weights, float* biases, float* input_vector, int size_of_input, int size_of_result, float* result){
	float temp_neuron = 0;
	float temp_weight, temp_input, temp_tensor;
	for (int hidden_neuron = 0; hidden_neuron < size_of_result; hidden_neuron++){
		for (int col = 0; col < size_of_input; col++){
			temp_weight = weights[(hidden_neuron*size_of_input) + col];
			temp_input = input_vector[col];
			temp_tensor = (temp_weight * temp_input);
			temp_neuron += temp_tensor;
		}
		/* Add bias & sigmoid */
		temp_neuron += biases[hidden_neuron];
		temp_neuron= networkPSsigmoid(temp_neuron);
		result[hidden_neuron] = temp_neuron;
		temp_neuron = 0;
	}
}

/* Hardware feedforward */
static void networkPLfeedforward(float* weights, float* biases, float* input_vector, int size_of_input, int size_of_result, float* result){
	float temp_neuron = 0;
	float temp_weight[size_of_input];
	for (int hidden_neuron = 0; hidden_neuron < size_of_result; hidden_neuron++){
		for (int col = 0; col < size_of_input; col++){
			temp_weight[col] = weights[(hidden_neuron*size_of_input) + col];
		}
		// Multiply & accumulate (Core instruction)
		Accelerator_call(temp_weight, input_vector, &temp_neuron);
		// Add bias & sigmoid
		temp_neuron += biases[hidden_neuron];
		temp_neuron= networkPSsigmoid(temp_neuron);
		result[hidden_neuron] = temp_neuron;
		temp_neuron = 0;
	}
}

/* Main function */
static void networkPSrun(){
	float hidden_result_sw[HIDDEN_SIZE];
	float hidden_result_hw[HIDDEN_SIZE];
	float final_output_sw[OUTPUT_SIZE];
	float final_output_hw[OUTPUT_SIZE];
	for (int image_index = 0; image_index < number_of_images; image_index++){
		/* Software feedforward */
		networkPSfeedforward(layer_0, bias_0, image[image_index], image_size, HIDDEN_SIZE, hidden_result_sw);
		/* Hardware feedforward */
		networkPLfeedforward(layer_0, bias_0, image[image_index], image_size, HIDDEN_SIZE, hidden_result_hw);

		/* Second feedforward */
		networkPSfeedforward(layer_1, bias_1, hidden_result_sw, HIDDEN_SIZE, OUTPUT_SIZE, final_output_sw);
		networkPSfeedforward(layer_1, bias_1, hidden_result_hw, HIDDEN_SIZE, OUTPUT_SIZE, final_output_hw);

		/* Evaluate the result */
		int predicted_result_sw = networkPSargmax(final_output_sw);
		int predicted_result_hw = networkPSargmax(final_output_hw);

		int probability_sw = (int)(final_output_sw[predicted_result_sw] * 1000000) % 1000000;
		int probability_hw = (int)(final_output_hw[predicted_result_hw] * 1000000) % 1000000;

		/* Compromise the result */
		if (predicted_result_sw != predicted_result_hw){
			xil_printf("Result Not match between SW and HW!\n");
			xil_printf("SW: Image id:%d [%d] - predict result [%d] with (0.%d)\n", image_index+1, ground_truth[image_index], predicted_result_sw, probability_sw);
		    xil_printf("HW: Image id:%d [%d] - predict result [%d] with (0.%d)\n", image_index+1, ground_truth[image_index], predicted_result_hw, probability_hw);
		} else {
			xil_printf("SW & HW matched!\n");
			xil_printf("Image id:%d [%d] - predict result [%d] with (0.%d)\n", image_index+1, ground_truth[image_index], predicted_result_sw, probability_sw);
		 }
	}
}


