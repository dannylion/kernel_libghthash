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
 * $Id: memory_functions.h 10/01/2016
 *
 ********************************************************************/

#ifndef __MEMORY_FUNCTIONS_H__
#define __MEMORY_FUNCTIONS_H__

#include "ght_hash_table.h"

#if defined(_WIN32) && defined(_KERNEL_MODE)
#include <ntddk.h>

#define LIBGHT_POOL_TAG ('THGL')
#else
#include <stdlib.h> /* malloc, free */
#endif

extern const ght_fn_alloc_t DefaultAllocFunction;
extern const ght_fn_free_t DefaultFreeFunction;

#endif /* __MEMORY_FUNCTIONS_H__ */
