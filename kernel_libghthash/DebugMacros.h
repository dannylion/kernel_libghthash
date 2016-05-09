/*********************************************************************
 * Written by Dan Li-on
 *
 * Filename:      memory_functions.h
 * Description:   Provide the needed memory functions for different architectures
 *
 * This program is free software; you can redistribute it and/or
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
 * $Id: debug.h 10/01/2016
 *
 ********************************************************************/

#if defined(_WIN32) && defined(_KERNEL_MODE)
#include <ntddk.h>
#else
#include <stdlib.h> /* perror */
#include <assert.h> /* assert */
#endif

#if defined(_WIN32) && defined(_KERNEL_MODE)

#define LOG_ERROR(errorMsg) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[E] %s[%d]-%s: %s\n", __FILE__, __LINE__, __FUNCTION__, errorMsg)
#define DEBUG_ASSERT(condition) NT_ASSERT(condition)

#define LOG_NTSTATUS(eStatus) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[E] %s[%d]-%s: NTSTATUS=%08X\n", __FILE__, __LINE__, __FUNCTION__, eStatus)

#else /* User-mode */

#define LOG_ERROR(errorMsg) perror(errorMsg)
#define DEBUG_ASSERT(condition) assert(condition)

#endif
