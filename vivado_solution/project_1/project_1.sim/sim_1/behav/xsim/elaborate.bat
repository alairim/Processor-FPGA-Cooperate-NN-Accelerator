@echo off
REM ****************************************************************************
REM Vivado (TM) v2018.3 (64-bit)
REM
REM Filename    : elaborate.bat
REM Simulator   : Xilinx Vivado Simulator
REM Description : Script for elaborating the compiled design
REM
REM Generated by Vivado on Thu Jan 12 16:20:50 +0100 2023
REM SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
REM
REM Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
REM
REM usage: elaborate.bat
REM
REM ****************************************************************************
call xelab  -wto d7151e23db8945639511bb736d3ddd2a --incr --debug typical --relax --mt 2 -L axi_infrastructure_v1_1_0 -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xil_defaultlib -L lib_pkg_v1_0_2 -L fifo_generator_v13_2_3 -L lib_fifo_v1_0_12 -L lib_srl_fifo_v1_0_2 -L lib_cdc_v1_0_2 -L axi_datamover_v5_1_20 -L axi_sg_v4_1_11 -L axi_dma_v7_1_19 -L proc_sys_reset_v5_0_13 -L xlconstant_v1_1_5 -L smartconnect_v1_0 -L xlconcat_v2_1_1 -L generic_baseblocks_v2_1_0 -L axi_register_slice_v2_1_18 -L axi_data_fifo_v2_1_17 -L axi_crossbar_v2_1_19 -L axi_protocol_converter_v2_1_18 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -L xpm --snapshot design_1_wrapper_behav xil_defaultlib.design_1_wrapper xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
