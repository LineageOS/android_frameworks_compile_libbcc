/* ===-- fixxfdi.c - Implement __fixxfdi -----------------------------------===
 *
 *      	       The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __fixxfdi for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */

#if !_ARCH_PPC

#include "int_lib.h"

/* Returns: convert a to a signed long long, rounding toward zero. */

/* Assumption: long double is an intel 80 bit floating point type padded with 6 bytes
 *             su_int is a 32 bit integral type
 *             value in long double is representable in di_int (no range checking performed)
 */

/* gggg gggg gggg gggg gggg gggg gggg gggg | gggg gggg gggg gggg seee eeee eeee eeee |
 * 1mmm mmmm mmmm mmmm mmmm mmmm mmmm mmmm | mmmm mmmm mmmm mmmm mmmm mmmm mmmm mmmm
 */

di_int
__fixxfdi(long double a)
{
    long_double_bits fb;
    fb.f = a;
    int e = (fb.u.high.s.low & 0x00007FFF) - 16383;
    if (e < 0)
        return 0;
    di_int s = -(si_int)((fb.u.high.s.low & 0x00008000) >> 15);
    di_int r = fb.u.low.all;
    r = (du_int)r >> (63 - e);
    return (r ^ s) - s;
}

#endif /* !_ARCH_PPC */
