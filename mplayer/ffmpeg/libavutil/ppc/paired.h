/*
 * Copyright (c) 2010-2011 Extrems <metaradil@gmail.com>
 *
 * This file is part of MPlayer CE.
 *
 * MPlayer CE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * MPlayer CE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with MPlayer CE; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_PPC_PAIRED_H
#define AVUTIL_PPC_PAIRED_H

//#include <paired.h>

#define vector register

typedef float vec_f32_t __attribute__((vector_size(8)));
typedef unsigned char vec_u8_t __attribute__((vector_size(2)));
typedef unsigned short vec_u16_t __attribute__((vector_size(4)));
typedef signed char vec_s8_t __attribute__((vector_size(2)));
typedef signed short vec_s16_t __attribute__((vector_size(4)));

enum {
	GQR_TYPE_FLOAT = 0,
	GQR_TYPE_U8 = 4,
	GQR_TYPE_U16,
	GQR_TYPE_S8,
	GQR_TYPE_S16,
};

#define psq_l(d, rA, W, I) ({ \
	vector float frD; \
	asm volatile("psq_l %0,%1(%2),%3,%4" \
	             : "=f"(frD) : "i"(d), "b"(rA), "i"(W), "i"(I) : "memory"); \
	frD; })

#define psq_lx(rA, rB, W, I) ({ \
	vector float frD; \
	asm volatile("psq_lx %0,%1,%2,%3,%4" \
	             : "=f"(frD) : "b"(rA), "r"(rB), "i"(W), "i"(I) : "memory"); \
	frD; })

#define psq_lu(d, rA, W, I) ({ \
	vector float frD; \
	asm volatile("psq_lu %0,%2(%1),%3,%4" \
	             : "=f"(frD), "+b"(rA) : "i"(d), "i"(W), "i"(I) : "memory"); \
	frD; })

#define psq_lux(rA, rB, W, I) ({ \
	vector float frD; \
	asm volatile("psq_lux %0,%1,%2,%3,%4" \
	             : "=f"(frD), "+b"(rA) : "r"(rB), "i"(W), "i"(I) : "memory"); \
	frD; })

#define psq_st(frD, d, rA, W, I) \
	asm volatile("psq_st %0,%1(%2),%3,%4" \
	             :: "f"(frD), "i"(d), "b"(rA), "i"(W), "i"(I) : "memory")

#define psq_stx(frD, rA, rB, W, I) \
	asm volatile("psq_stx %0,%1,%2,%3,%4" \
	             :: "f"(frD), "b"(rA), "r"(rB), "i"(W), "i"(I) : "memory")

#define psq_stu(frD, d, rA, W, I) \
	asm volatile("psq_stu %1,%2(%0),%3,%4" \
	             : "+b"(rA) : "f"(frD), "i"(d), "i"(W), "i"(I) : "memory")

#define psq_stux(frD, rA, rB, W, I) \
	asm volatile("psq_stux %1,%0,%2,%3,%4" \
	             : "+b"(rA) : "f"(frD), "r"(rB), "i"(W), "i"(I) : "memory")

#define ps_neg(frB) ({ \
	vector float frD; \
	asm("ps_neg %0,%1" : "=f"(frD) : "f"(frB)); \
	frD; })

#define ps_add(frA, frB) ({ \
	vector float frD; \
	asm("ps_add %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_sub(frA, frB) ({ \
	vector float frD; \
	asm("ps_sub %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_mul(frA, frC) ({ \
	vector float frD; \
	asm("ps_mul %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frC)); \
	frD; })

#define ps_madd(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_madd %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_madds0(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_madds0 %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_madds1(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_madds1 %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_msub(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_msub %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_muls0(frA, frC) ({ \
	vector float frD; \
	asm("ps_muls0 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frC)); \
	frD; })

#define ps_muls1(frA, frC) ({ \
	vector float frD; \
	asm("ps_muls1 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frC)); \
	frD; })

#define ps_nmadd(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_nmadd %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_nmsub(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_nmsub %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_merge00(frA, frB) ({ \
	vector float frD; \
	asm("ps_merge00 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_merge01(frA, frB) ({ \
	vector float frD; \
	asm("ps_merge01 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_merge10(frA, frB) ({ \
	vector float frD; \
	asm("ps_merge10 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_merge11(frA, frB) ({ \
	vector float frD; \
	asm("ps_merge11 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_sel(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_sel %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_sum0(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_sum0 %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_sum1(frA, frC, frB) ({ \
	vector float frD; \
	asm("ps_sum1 %0,%1,%2,%3" : "=f"(frD) : "f"(frA), "f"(frC), "f"(frB)); \
	frD; })

#define ps_cmpu0(crfD, frA, frB) ({ \
	vector float frD; \
	asm volatile("ps_cmpu0 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#define ps_cmpu1(crfD, frA, frB) ({ \
	vector float frD; \
	asm volatile("ps_cmpu1 %0,%1,%2" : "=f"(frD) : "f"(frA), "f"(frB)); \
	frD; })

#if 1
#define paired_msub ps_msub
#define paired_madd ps_madd
#define paired_nmsub ps_nmsub
#define paired_nmadd ps_nmadd
#define paired_sum0 ps_sum0
#define paired_sum1 ps_sum1
#define paired_add ps_add
#define paired_sub ps_sub
#define paired_mul ps_mul
#define paired_muls0 ps_muls0
#define paired_muls1 ps_muls1
#define paired_madds0 ps_madds0
#define paired_madds1 ps_madds1
#define paired_merge00 ps_merge00
#define paired_merge01 ps_merge01
#define paired_merge10 ps_merge10
#define paired_merge11 ps_merge11
#define paired_neg ps_neg
#define paired_stx(frD,rB,rA) psq_stx(frD,rA,rB,0,0)
#define paired_lx(rB,rA) psq_lx(rA,rB,0,0)

#define paired_sel ps_sel
#define paired_cmpu0 ps_cmpu0
#define paired_cmpu1 ps_cmpu1

#define LT            0
#define GT            1
#define EQ            2
#define UN            3
#endif

#endif /* AVUTIL_PPC_PAIRED_H */
