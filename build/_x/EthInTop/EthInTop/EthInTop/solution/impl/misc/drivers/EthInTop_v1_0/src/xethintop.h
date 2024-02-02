// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XETHINTOP_H
#define XETHINTOP_H

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
#include "xethintop_hw.h"

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
} XEthintop_Config;
#endif

typedef struct {
    u32 Control_BaseAddress;
    u32 IsReady;
} XEthintop;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XEthintop_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XEthintop_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XEthintop_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XEthintop_ReadReg(BaseAddress, RegOffset) \
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
int XEthintop_Initialize(XEthintop *InstancePtr, u16 DeviceId);
XEthintop_Config* XEthintop_LookupConfig(u16 DeviceId);
int XEthintop_CfgInitialize(XEthintop *InstancePtr, XEthintop_Config *ConfigPtr);
#else
int XEthintop_Initialize(XEthintop *InstancePtr, const char* InstanceName);
int XEthintop_Release(XEthintop *InstancePtr);
#endif

void XEthintop_Start(XEthintop *InstancePtr);
u32 XEthintop_IsDone(XEthintop *InstancePtr);
u32 XEthintop_IsIdle(XEthintop *InstancePtr);
u32 XEthintop_IsReady(XEthintop *InstancePtr);
void XEthintop_EnableAutoRestart(XEthintop *InstancePtr);
void XEthintop_DisableAutoRestart(XEthintop *InstancePtr);

void XEthintop_Set_in_r(XEthintop *InstancePtr, u64 Data);
u64 XEthintop_Get_in_r(XEthintop *InstancePtr);
void XEthintop_Set_buffSize(XEthintop *InstancePtr, u32 Data);
u32 XEthintop_Get_buffSize(XEthintop *InstancePtr);

void XEthintop_InterruptGlobalEnable(XEthintop *InstancePtr);
void XEthintop_InterruptGlobalDisable(XEthintop *InstancePtr);
void XEthintop_InterruptEnable(XEthintop *InstancePtr, u32 Mask);
void XEthintop_InterruptDisable(XEthintop *InstancePtr, u32 Mask);
void XEthintop_InterruptClear(XEthintop *InstancePtr, u32 Mask);
u32 XEthintop_InterruptGetEnabled(XEthintop *InstancePtr);
u32 XEthintop_InterruptGetStatus(XEthintop *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
