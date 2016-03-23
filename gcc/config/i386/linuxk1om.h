/* Definitions for Intel K1OM running Linux-based GNU systems with ELF
   format.
   Copyright (C) 2011
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#undef TARGET_SUBTARGET32_ISA_DEFAULT
#define TARGET_SUBTARGET32_ISA_DEFAULT OPTION_MASK_ISA_KNC

#undef TARGET_SUBTARGET64_ISA_DEFAULT
#define TARGET_SUBTARGET64_ISA_DEFAULT TARGET_SUBTARGET32_ISA_DEFAULT

#undef TARGET_SUBTARGET64_DEFAULT
#define TARGET_SUBTARGET64_DEFAULT (MASK_128BIT_LONG_DOUBLE)

#undef GLIBC_DYNAMIC_LINKER64
#define GLIBC_DYNAMIC_LINKER64 "/lib64/ld-linux-k1om.so.2"

#undef ASM_SPEC
#define ASM_SPEC "%{" SPEC_32 ":--32} %{" SPEC_64 ":--march=k1om}"

#undef	LINK_SPEC
#define LINK_SPEC "%{" SPEC_64 ":-m elf_k1om} %{" SPEC_32 ":-m elf_i386} \
  %{shared:-shared} \
  %{!shared: \
    %{!static: \
      %{rdynamic:-export-dynamic} \
      %{" SPEC_32 ":-dynamic-linker " GLIBC_DYNAMIC_LINKER32 "} \
      %{" SPEC_64 ":-dynamic-linker " GLIBC_DYNAMIC_LINKER64 "}} \
    %{static:-static}}"
