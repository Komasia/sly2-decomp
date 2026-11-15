/* BindRootBlend (0x1A0300): binds a root blend's eight entries to an object: for each entry with a segment, finds the
 * segment's root channel and stores the root's average velocity over the segment ((pos(0) - pos(tMax)) / tMax);
 * then makes the eight-entry blend (NewBlend, 0x20-byte entries) and returns it in *ppmulti. SafeHouse actanim.cpp. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union WORD { unsigned int bits; float value; } WORD;
typedef union U { qword q; float f[4]; } U;
struct ACTOR; struct MULTI;
struct EVAL;
struct EVAL { VTENT *vt; };            /* a channel's evaluator: vtable slot 3 evaluates it at a time */
struct CHN { int x0; struct EVAL *peval; };  /* the segment's root channel (PchnFindAseg) */
struct ASEG { char pad[0x74]; WORD tMax; };   /* +0x74: the segment's length */
struct ROOTBLENDE { float weight; struct ASEG *paseg; int pad[2]; qword vel; };  /* one of the 8 root blend entries */
struct CHN *PchnFindAseg__FP4ASEGP3ALOPvi(struct ASEG *paseg, struct ACTOR *palo, void *pv, int f);
void NewBlend__FP3ALOiiP4ELEMiPiT5Pv(struct ACTOR *palo, int cb, int c, struct ROOTBLENDE *ae, int count, int *keys, int *counts, struct MULTI **ppmulti);
#define FIELD_OFFSET(t,m) ((unsigned int)&(((struct t*)0x10000)->m)-0x10000)
typedef char EVAL_vt_Offset[FIELD_OFFSET(EVAL,vt)==0?1:-1];
typedef char CHN_peval_Offset[FIELD_OFFSET(CHN,peval)==4?1:-1];
typedef char ASEG_tMax_Offset[FIELD_OFFSET(ASEG,tMax)==116?1:-1];
typedef char ROOTBLENDE_weight_Offset[FIELD_OFFSET(ROOTBLENDE,weight)==0?1:-1];
typedef char ROOTBLENDE_paseg_Offset[FIELD_OFFSET(ROOTBLENDE,paseg)==4?1:-1];
typedef char ROOTBLENDE_vel_Offset[FIELD_OFFSET(ROOTBLENDE,vel)==16?1:-1];
typedef char EVAL_PrefixSize[sizeof(struct EVAL)==4?1:-1];
typedef char CHN_PrefixSize[sizeof(struct CHN)==8?1:-1];
typedef char ASEG_PrefixSize[sizeof(struct ASEG)==120?1:-1];
typedef char ROOTBLENDE_Size[sizeof(struct ROOTBLENDE)==32?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char WORD_Size[sizeof(WORD)==4?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
// name: SafeHouse port (BindRootBlend)
void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(struct ACTOR *palo, struct ROOTBLENDE *ae, struct MULTI **ppmulti)
{
    struct ROOTBLENDE *pe = ae;
    int i;
    U posStart, posEnd, t;
    struct MULTI *pmulti;
    for (i = 0; i < 8; i++, pe++) {
        if (pe->paseg) {
            struct CHN *pchn = PchnFindAseg__FP4ASEGP3ALOPvi(pe->paseg, palo, (void *)1, 1);
            if (pchn) {
                ((void (*)(struct EVAL *, float, float, qword *, void *))pchn->peval->vt[3].pfn)((struct EVAL *)VT_THIS(pchn->peval, &pchn->peval->vt[3]), 0.0f, 1.0f, &posStart.q, 0);
                ((void (*)(struct EVAL *, float, float, qword *, void *))pchn->peval->vt[3].pfn)((struct EVAL *)VT_THIS(pchn->peval, &pchn->peval->vt[3]), pe->paseg->tMax.value, 1.0f, &posEnd.q, 0);
                {
                    /* pe->vel = (posStart - posEnd) / tMax */
                    register qword d __asm__("vf2");
                    register qword scalar __asm__("vf1");
                    register struct ASEG *paseg __asm__("$2") = pe->paseg;
                    register unsigned int bits __asm__("$2") = paseg->tMax.bits;
                    __asm__("qmtc2.ni %1, %0" : "=j"(scalar) : "r"(bits));
                    d = posStart.q;
                    __asm__("vsub.xyzw %0, %0, %1" : "+j"(d) : "j"(posEnd.q));
                    t.q = scalar;
                    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(d) : "j"(t.q));
                    pe->vel = d;
                }
            }
        }
    }
    NewBlend__FP3ALOiiP4ELEMiPiT5Pv(palo, 0x20, 8, ae, 0, 0, 0, &pmulti);
    *ppmulti = pmulti;
}
