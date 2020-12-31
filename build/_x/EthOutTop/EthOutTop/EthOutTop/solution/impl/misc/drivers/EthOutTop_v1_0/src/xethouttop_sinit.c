// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xethouttop.h"

extern XEthouttop_Config XEthouttop_ConfigTable[];

XEthouttop_Config *XEthouttop_LookupConfig(u16 DeviceId) {
	XEthouttop_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XETHOUTTOP_NUM_INSTANCES; Index++) {
		if (XEthouttop_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XEthouttop_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XEthouttop_Initialize(XEthouttop *InstancePtr, u16 DeviceId) {
	XEthouttop_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XEthouttop_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XEthouttop_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

