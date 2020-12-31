// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xethouttop.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XEthouttop_CfgInitialize(XEthouttop *InstancePtr, XEthouttop_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XEthouttop_Start(XEthouttop *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL) & 0x80;
    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XEthouttop_IsDone(XEthouttop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XEthouttop_IsIdle(XEthouttop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XEthouttop_IsReady(XEthouttop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XEthouttop_EnableAutoRestart(XEthouttop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XEthouttop_DisableAutoRestart(XEthouttop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_AP_CTRL, 0);
}

void XEthouttop_Set_out_r(XEthouttop *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XEthouttop_Get_out_r(XEthouttop *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XEthouttop_Set_buffSize(XEthouttop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_BUFFSIZE_DATA, Data);
}

u32 XEthouttop_Get_buffSize(XEthouttop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_BUFFSIZE_DATA);
    return Data;
}

void XEthouttop_InterruptGlobalEnable(XEthouttop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_GIE, 1);
}

void XEthouttop_InterruptGlobalDisable(XEthouttop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_GIE, 0);
}

void XEthouttop_InterruptEnable(XEthouttop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_IER);
    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_IER, Register | Mask);
}

void XEthouttop_InterruptDisable(XEthouttop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_IER);
    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_IER, Register & (~Mask));
}

void XEthouttop_InterruptClear(XEthouttop *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XEthouttop_WriteReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_ISR, Mask);
}

u32 XEthouttop_InterruptGetEnabled(XEthouttop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_IER);
}

u32 XEthouttop_InterruptGetStatus(XEthouttop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEthouttop_ReadReg(InstancePtr->Control_BaseAddress, XETHOUTTOP_CONTROL_ADDR_ISR);
}

