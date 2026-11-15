/* Splice reference payloads (C sources): the refcounted slot-heap nodes behind CRef's vector / matrix / clq /
 * lm / smp tags, and the pools they come from. Layouts from InitTag 0x12A0B0, Incref 0x129DF8 (the refcount
 * offsets 0x10 / 0x40 / 0x10 / 0x08 / 0x0C) and the CRef::SetXxx setters 0x1296A8..0x1298F0; node names are ours.
 * Sly 1's TAG union (splice/ref.h) points straight at the value: m_pvector / m_pmatrix / m_pclq / ..., which is
 * the first member of each node here.
 */
#ifndef SPLICE_REF_H
#define SPLICE_REF_H
#include "splice.h"
#include "util.h"

/* Sly 1 util.h SMP: a spring-damped move (fast / slow speed, fast duration) */
typedef struct SMP {
    float svFast;
    float svSlow;
    float dtFast;
} SMP;

typedef struct REFVECTOR { qword vec; int cref; } REFVECTOR;       /* tag TAGK_Vector: the VECTOR as one quadword */
typedef struct REFMATRIX { struct MATRIX4 mat; int cref; } REFMATRIX;  /* tag TAGK_Matrix */
typedef struct REFCLQ { qword clq; int cref; } REFCLQ;             /* tag TAGK_Clq: the CLQ as one quadword */
typedef struct REFLM { LM lm; int cref; } REFLM;                   /* tag TAGK_Lm */
typedef struct REFSMP { SMP smp; int cref; } REFSMP;               /* tag TAGK_Smp */

/* The per-kind node pools (slot heaps of 0x18 bytes each, see 0x11CCC0) */
struct REFPOOL;
extern struct REFPOOL D_00452188;   /* REFVECTOR nodes */
extern struct REFPOOL D_004521A0;   /* REFMATRIX nodes */
extern struct REFPOOL D_004521B8;   /* REFCLQ nodes */
extern struct REFPOOL D_004521D0;   /* REFLM nodes */
extern struct REFPOOL D_004521E8;   /* REFSMP nodes */

/* 0x11CCC0: takes a cleared node from a pool (carving a new block when its free list is empty) */
void *func_0011CCC0(struct REFPOOL *ppool);

#endif
