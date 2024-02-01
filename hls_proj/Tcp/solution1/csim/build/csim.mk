# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__HLS_FPO_v6_1__ = 1

__SIM_MATHHLS__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../../src/Tcp/Test/TcpTest.cpp ../../../../../src/Tcp/TcpTop.cpp ../../../../../src/Tcp/TcpPayloadParsor.cpp ../../../../../src/Tcp/TcpSend.cpp ../../../../../src/Tcp/TcpManager.cpp ../../../../../src/Tcp/TcpInputProcessor.cpp ../../../../../src/Tcp/Counter.cpp

override TARGET := csim.exe

AUTOPILOT_ROOT := /opt/Xilinx/Vitis/2020.1
AUTOPILOT_MACH := lnx64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
IFLAG += -fPIC
ifndef AP_GCC_PATH
  AP_GCC_PATH := /opt/Xilinx/Vivado/2020.1/tps/lnx64/gcc-6.2.0/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_TOOL}/clang-3.9/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_TOOL}/systemc/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -D__SIM_FPO__

IFLAG += -D__HLS_FPO_v6_1__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E2__
IFLAG += -Wno-unknown-pragmas 
LFLAG += -lpcap
IFLAG += -g
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += -Werror=return-type
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



$(ObjDir)/TcpTest.o: ../../../../../src/Tcp/Test/TcpTest.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/Test/TcpTest.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -Wno-unknown-pragmas -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpTest.d

$(ObjDir)/TcpTop.o: ../../../../../src/Tcp/TcpTop.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/TcpTop.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpTop.d

$(ObjDir)/TcpPayloadParsor.o: ../../../../../src/Tcp/TcpPayloadParsor.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/TcpPayloadParsor.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpPayloadParsor.d

$(ObjDir)/TcpSend.o: ../../../../../src/Tcp/TcpSend.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/TcpSend.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpSend.d

$(ObjDir)/TcpManager.o: ../../../../../src/Tcp/TcpManager.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/TcpManager.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpManager.d

$(ObjDir)/TcpInputProcessor.o: ../../../../../src/Tcp/TcpInputProcessor.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/TcpInputProcessor.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/TcpInputProcessor.d

$(ObjDir)/Counter.o: ../../../../../src/Tcp/Counter.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../src/Tcp/Counter.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/Counter.d
