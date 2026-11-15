/* TeleportActor (0x2052E0): STEP vt slot 38: places the object at ploDest's matrix (vt slot 31) with its base
 * offset vecBase taken back (vt slots 29 / 30); an actor's camera target goes sHeight above the place; the
 * velocities are zeroed (slots 35 / 36) and the floor contact forgotten. A destination that is not an XFM-derived
 * object (cid 3) goes to the ALO version (0x1F49C8). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f; } U;
typedef union {float value;int word;} FLOATWORD;
typedef struct M4 { qword row[4]; } M4;
typedef struct BASIC {int unk_0x00,unk_0x04,unk_0x08; VTENT *pvt;} BASIC;
typedef struct STEP {
    BASIC basic;
    char pad[0x208 - 0x10]; int pxpFloor;    /* the floor contact */
    char pad2[0x240 - 0x20C]; qword vecBase;
    char pad3[0x1048 - 0x250]; FLOATWORD sHeight;    /* ACTOR: height of the camera target */
    char pad4[0x1060 - 0x104C]; qword posCmTarget;    /* ACTOR: the last camera target (field: SafeHouse port) */
} STEP;
#define CID_XFM 3
#define CID_ACTOR 0x34
extern qword D_002A2DD0, g_normalZ;
extern int FIsBasicDerivedFrom__FP5BASIC3CID(BASIC *, int);
extern void func_001F49C8(STEP *, BASIC *);
static inline qword Transform(const M4*m,qword v,qword last,qword*published){
 register qword result __asm__("vf7"),argument __asm__("$5"),origin __asm__("vf1")=last;
 __asm__ volatile("vmulax.xyz $ACC,%3,%7x\n\tvmadday.xyz $ACC,%4,%7y\n\tvmaddaz.xyz $ACC,%5,%7z\n\tvmaddw.xyz %0,%6,$vf0w\n\tqmfc2.ni %1,%0\n\tsqc2 %6,%2"
  :"=&j"(result),"=&r"(argument),"=m"(*published):"j"(m->row[0]),"j"(m->row[1]),"j"(m->row[2]),"j"(origin),"j"(v));
 return argument;
}
static inline qword Broadcast(float f){register qword r __asm__("vf6");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword MulX(qword v,qword s){register qword r __asm__("vf2");__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
// name: SafeHouse port (TeleportActor)
extern void TeleportActor__FP2LOT0(STEP *pstep, BASIC *ploDest)
{
    if (!ploDest) return;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(ploDest, CID_XFM)) {
        M4 m;
        U scale;
        register qword v __asm__("vf2");
        register VTENT *set __asm__("a2");
        VTENT *get = &ploDest->pvt[31];
        const M4 *source = ((M4 *(*)(BASIC *))get->pfn)((BASIC *)VT_THIS(ploDest, get));
        m.row[0] = source->row[0];
        set = pstep->basic.pvt;
        {qword sc = Broadcast(-1.0f);
        m.row[1] = source->row[1];
        v = MulX(pstep->vecBase, sc);
        m.row[2] = source->row[2];
        {qword t = Transform(&m,v,source->row[3],&m.row[3]);
        STEP *self = (STEP *)VT_THIS(pstep, &set[29]);
        register void (*positionFn)(STEP*,qword) __asm__("v1")=(void(*)(STEP*,qword))set[29].pfn;
        scale.q = sc;
        positionFn(self, t);}}
        { VTENT *s=pstep->basic.pvt; ((void (*)(STEP *,const M4 *))s[30].pfn)((STEP *)VT_THIS(pstep, &s[30]), &m); }
        if (FIsBasicDerivedFrom__FP5BASIC3CID(&pstep->basic,CID_ACTOR)) {
            qword r;
            __asm__("qmtc2.ni %1,%0" : "=j"(scale.q) : "r"(pstep->sHeight.word));
            r = m.row[3];
            __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(r) : "j"(g_normalZ), "j"(scale.q));
            pstep->posCmTarget = r;
        }
        { VTENT *s=pstep->basic.pvt; ((void (*)(STEP *,qword))s[35].pfn)((STEP *)VT_THIS(pstep, &s[35]), D_002A2DD0); }
        { VTENT *s=pstep->basic.pvt; ((void (*)(STEP *,qword))s[36].pfn)((STEP *)VT_THIS(pstep, &s[36]), D_002A2DD0); }
        pstep->pxpFloor = 0;
    } else {
        func_001F49C8(pstep,ploDest);
    }
}

typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_scalar[(sizeof(U)==16)?1:-1];
typedef char layout_word[(sizeof(FLOATWORD)==4)?1:-1];
typedef char layout_word_value[((unsigned)&((FLOATWORD*)0)->value==0)?1:-1];
typedef char layout_word_bits[((unsigned)&((FLOATWORD*)0)->word==0)?1:-1];
typedef char layout_matrix[(sizeof(M4)==0x40)?1:-1];
typedef char layout_matrix_0[((unsigned)&((M4*)0)->row[0]==0)?1:-1];
typedef char layout_matrix_1[((unsigned)&((M4*)0)->row[1]==0x10)?1:-1];
typedef char layout_matrix_2[((unsigned)&((M4*)0)->row[2]==0x20)?1:-1];
typedef char layout_matrix_3[((unsigned)&((M4*)0)->row[3]==0x30)?1:-1];
typedef char layout_base[(sizeof(BASIC)==0x10)?1:-1];
typedef char layout_vtable[((unsigned)&((BASIC*)0)->pvt==0xC)?1:-1];
typedef char layout_count[((unsigned)&((STEP*)0)->pxpFloor==0x208)?1:-1];
typedef char layout_offset[((unsigned)&((STEP*)0)->vecBase==0x240)?1:-1];
typedef char layout_amount[((unsigned)&((STEP*)0)->sHeight==0x1048)?1:-1];
typedef char layout_adjusted[((unsigned)&((STEP*)0)->posCmTarget==0x1060)?1:-1];
