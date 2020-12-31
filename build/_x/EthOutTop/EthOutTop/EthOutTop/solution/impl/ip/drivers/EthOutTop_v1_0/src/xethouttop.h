// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XETHOUTTOP_H
#define XETHOUTTOP_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xethouttop_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XEthouttop_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XEthouttop;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XEthouttop_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XEthouttop_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XEthouttop_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XEthouttop_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XEthouttop_Initialize(XEthouttop *InstancePtr, u16 DeviceId);
XEthouttop_Config* XEthouttop_LookupConfig(u16 DeviceId);
int XEthouttop_CfgInitialize(XEthouttop *InstancePtr, XEthouttop_Config *ConfigPtr);
#else
int XEthouttop_Initialize(XEthouttop *InstancePtr, const char* InstanceName);
int XEthouttop_Release(XEthouttop *InstancePtr);
#endif

void XEthouttop_Start(XEthouttop *InstancePtr);
u32 XEthouttop_IsDone(XEthouttop *InstancePtr);
u32 XEthouttop_IsIdle(XEthouttop *InstancePtr);
u32 XEthouttop_IsReady(XEthouttop *InstancePtr);
void XEthouttop_EnableAutoRestart(XEthouttop *InstancePtr);
void XEthouttop_DisableAutoRestart(XEthouttop *InstancePtr);

void XEthouttop_Set_out_r(XEthouttop *InstancePtr, u64 Data);
u64 XEthouttop_Get_out_r(XEthouttop *InstancePtr);
void XEthouttop_Set_buffSize(XEthouttop *InstancePtr, u32 Data);
u32 XEthouttop_Get_buffSize(XEthouttop *InstancePtr);

void XEthouttop_InterruptGlobalEnable(XEthouttop *InstancePtr);
void XEthouttop_InterruptGlobalDisable(XEthouttop *InstancePtr);
void XEthouttop_InterruptEnable(XEthouttop *InstancePtr, u32 Mask);
void XEthouttop_InterruptDisable(XEthouttop *InstancePtr, u32 Mask);
void XEthouttop_InterruptClear(XEthouttop *InstancePtr, u32 Mask);
u32 XEthouttop_InterruptGetEnabled(XEthouttop *InstancePtr);
u32 XEthouttop_InterruptGetStatus(XEthouttop *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
