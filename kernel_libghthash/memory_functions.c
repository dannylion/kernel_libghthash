/*********************************************************************
 * Written by Dan Li-on
 *
 * Filename:      memory_functions.h
 * Description:   Provide the needed memory functions for different architectures
 *
 * This program is DefaultFreeFunction software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * $Id: memory_functions.c 10/01/2016
 *
 ********************************************************************/

#include "debug.h"
#include "memory_functions.h"

#if defined(_WIN32) && defined(_KERNEL_MODE)
#include <ntddk.h>

void * 
AllocateFromNPagedPool(
	__in const size_t size 
)
{
	PVOID pvAllocated = NULL;
	NTSTATUS eStatus = STATUS_NO_MEMORY;

	NT_ASSERT(DISPATCH_LEVEL >= KeGetCurrentIrql());

	if (size)
	{
		pvAllocated = ExAllocatePoolWithTag(NonPagedPool, size, LIBGHT_POOL_TAG);
		if (!pvAllocated)
		{
			goto lblCleanup;
		}

		RtlZeroMemory(pvAllocated, size);
	}

	eStatus = STATUS_SUCCESS;

lblCleanup:
	if (!NT_SUCCESS(eStatus))
	{
		LOG_NTSTATUS(eStatus);
	}
	return pvAllocated;
}

void 
FreeFromNPagedPool(
	__in void * memblock 
)
{
	if (memblock)
	{
		ExFreePool(memblock);
	}
}

const ght_fn_alloc_t	DefaultAllocFunction	= (ght_fn_alloc_t)(&AllocateFromNPagedPool);
const ght_fn_free_t		DefaultFreeFunction		= (ght_fn_free_t)(&FreeFromNPagedPool);

#else

/* Compiled for user-mode, use regular DefaultAllocFunction and DefaultFreeFunction */
const ght_fn_alloc_t	DefaultAllocFunction	= (ght_fn_alloc_t)malloc;
const ght_fn_free_t		DefaultFreeFunction		= (ght_fn_free_t)free;

#endif
