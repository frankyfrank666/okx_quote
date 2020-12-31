// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xethintop.h"

extern XEthintop_Config XEthintop_ConfigTable[];

XEthintop_Config *XEthintop_LookupConfig(u16 DeviceId) {
	XEthintop_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XETHINTOP_NUM_INSTANCES; Index++) {
		if (XEthintop_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XEthintop_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEthintop_Initialize(XEthintop *InstancePtr, u16 DeviceId) {
	XEthintop_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEthintop_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEthintop_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

