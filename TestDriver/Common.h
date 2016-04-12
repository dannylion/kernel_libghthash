#pragma once

#include <fltKernel.h>
#include <intrin.h>

#ifdef _WIN64
#define IS_X64 TRUE
#else
#define IS_X64 FALSE
#endif

#ifdef DBG
#define IS_RELEASE FALSE
#else
#define IS_RELEASE TRUE
#endif

#ifndef STATIC
#define STATIC static
#endif

#define POOL_TAG ('thgT')

#define DEVICE_NAME			L"\\Device\\TestKLibght"
#define DEVICE_DOS_NAME		L"\\DosDevices\\TestKLibght"

typedef struct _DRIVER_GLOBALS
{
	PDEVICE_OBJECT	ptDeviceObject;
	BOOLEAN			bSymbolicLinkCreated;
} DRIVER_GLOBALS, *PDRIVER_GLOBALS;

EXTERN_C DRIVER_GLOBALS g_tDriverGlobals;

#define IO_COMPLETE_IRP(ptIrp, eStatus, dwInformation)			\
	{															\
		if (NULL != ptIrp)										\
		{														\
			(ptIrp)->IoStatus.Information = (dwInformation);	\
			(ptIrp)->IoStatus.Status = (eStatus);				\
			IoCompleteRequest((ptIrp), IO_NO_INCREMENT);		\
		}														\
	}

