// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xethintop.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XEthintop_CfgInitialize(XEthintop *InstancePtr, XEthintop_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XEthintop_Start(XEthintop *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL) & 0x80;
    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XEthintop_IsDone(XEthintop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XEthintop_IsIdle(XEthintop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XEthintop_IsReady(XEthintop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XEthintop_EnableAutoRestart(XEthintop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XEthintop_DisableAutoRestart(XEthintop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_AP_CTRL, 0);
}

void XEthintop_Set_in_r(XEthintop *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XEthintop_Get_in_r(XEthintop *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XEthintop_Set_buffSize(XEthintop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_BUFFSIZE_DATA, Data);
}

u32 XEthintop_Get_buffSize(XEthintop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_BUFFSIZE_DATA);
    return Data;
}

void XEthintop_InterruptGlobalEnable(XEthintop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_GIE, 1);
}

void XEthintop_InterruptGlobalDisable(XEthintop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_GIE, 0);
}

void XEthintop_InterruptEnable(XEthintop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IER);
    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IER, Register | Mask);
}

void XEthintop_InterruptDisable(XEthintop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IER);
    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IER, Register & (~Mask));
}

void XEthintop_InterruptClear(XEthintop *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthintop_WriteReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_ISR, Mask);
}

u32 XEthintop_InterruptGetEnabled(XEthintop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_IER);
}

u32 XEthintop_InterruptGetStatus(XEthintop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEthintop_ReadReg(InstancePtr->Control_BaseAddress, XETHINTOP_CONTROL_ADDR_ISR);
}

