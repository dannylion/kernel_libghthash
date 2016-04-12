#include <fltKernel.h>
#include <windef.h>
#include <InitGuid.h>
#include <devguid.h>
#include <wdmsec.h>

#include "ght_hash_table.h"

#include "Common.h"
#include "Test.h"

DRIVER_GLOBALS g_tDriverGlobals = {0};

STATIC
NTSTATUS
DriverEmptyIrpStub(
	_In_ PDEVICE_OBJECT ptDeviceObject,
	_In_ PIRP ptIrp
)
{
	NTSTATUS eStatus = STATUS_SUCCESS;
	UNREFERENCED_PARAMETER(ptDeviceObject);

	PAGED_CODE();

	IO_COMPLETE_IRP(ptIrp, eStatus, 0);
	return eStatus;
}

VOID
DriverUnload(
	PDRIVER_OBJECT ptDriverObject
)
{
	UNICODE_STRING usDosDeviceName = RTL_CONSTANT_STRING(DEVICE_DOS_NAME);

	UNREFERENCED_PARAMETER(ptDriverObject);

	if (g_tDriverGlobals.bSymbolicLinkCreated)
	{
		IoDeleteSymbolicLink(&usDosDeviceName);
		g_tDriverGlobals.bSymbolicLinkCreated = FALSE;
	}
	if (NULL != g_tDriverGlobals.ptDeviceObject)
	{
		IoDeleteDevice(g_tDriverGlobals.ptDeviceObject);
		g_tDriverGlobals.ptDeviceObject = NULL;
	}
}

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT ptDriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS		eStatus			= STATUS_UNSUCCESSFUL;
	UNICODE_STRING	usDeviceName	= RTL_CONSTANT_STRING(DEVICE_NAME);
	UNICODE_STRING	usDosDeviceName	= RTL_CONSTANT_STRING(DEVICE_DOS_NAME);

	PAGED_CODE();
	NT_ASSERT(NULL != ptDriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	ptDriverObject->DriverUnload = DriverUnload;

	eStatus = IoCreateDeviceSecure(
		ptDriverObject, 
		0, 
		&usDeviceName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RWX_RES_RWX,
		&GUID_DEVCLASS_SYSTEM,
		&g_tDriverGlobals.ptDeviceObject);
	if (!NT_SUCCESS(eStatus))
	{
		goto lblCleanup;
	}

	eStatus = IoCreateSymbolicLink(&usDosDeviceName, &usDeviceName);
	if (!NT_SUCCESS(eStatus))
	{
		goto lblCleanup;
	}
	g_tDriverGlobals.bSymbolicLinkCreated = TRUE;

	TEST_RunTests();

	// We must provide these 2 major functions, even if they don't do anything
	ptDriverObject->MajorFunction[IRP_MJ_CREATE]			= DriverEmptyIrpStub;
	ptDriverObject->MajorFunction[IRP_MJ_CLOSE]				= DriverEmptyIrpStub;
	ptDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= DriverEmptyIrpStub;

	g_tDriverGlobals.ptDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;
	g_tDriverGlobals.ptDeviceObject->Flags|=DO_BUFFERED_IO;

	eStatus = STATUS_SUCCESS;

lblCleanup:
	if (!NT_SUCCESS(eStatus))
	{
		DriverUnload(ptDriverObject);
	}

	return eStatus;
}
