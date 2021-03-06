/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"@(#)symbol.c	1.2	05/06/08 SMI"

#include <sys/types.h>
#include <string.h>

#include "symbol.h"

int
ignore_symbol(GElf_Sym *sym, const char *name)
{
	uchar_t type = GELF_ST_TYPE(sym->st_info);

	/*
	 * As an optimization, we do not output function or data object
	 * records for undefined or anonymous symbols.
	 */
	if (sym->st_shndx == SHN_UNDEF || sym->st_name == 0)
		return (1);

	/*
	 * _START_ and _END_ are added to the symbol table by the
	 * linker, and will never have associated type information.
	 */
	if (strcmp(name, "_START_") == 0 || strcmp(name, "_END_") == 0)
		return (1);

	/*
	 * Do not output records for absolute-valued object symbols
	 * that have value zero.  The compiler insists on generating
	 * things like this for __fsr_init_value settings, etc.
	 */
	if (type == STT_OBJECT && sym->st_shndx == SHN_ABS &&
	    sym->st_value == 0)
		return (1);
	return (0);
}
