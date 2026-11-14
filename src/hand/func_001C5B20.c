#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct POS { char pad[0x70]; qword pos; };
struct SHAPE {
    struct POS *pos; int pad4; float radius; int padC;
    unsigned long flags; char pad18[0xB0-0x18];
};
struct SO { char pad[0xE0]; int count; struct SHAPE *shapes; };
struct S { char pad[0xC]; VTENT *vt; char pad10[0x1DC-0x10]; float radius; };
struct Q { int enabled,pad4; float radius; struct SO *so; };
extern float D_002C0D7C;
qword PosOfLo__FP2LO(void *);
int SphereBspContacts__FG9VU_VECTORfP6SOPARTP3BSPiT3iP9CMCONTACT(qword,struct SHAPE *,int mask,int triangleCount,void *triangles,int capacity,void *contacts,float radius);
static inline void Trigger(struct S *p)
{
    VTENT *m=&p->vt[76];
    ((void (*)(void *,int))m->pfn)(VT_THIS(p, m),1);
}
static inline qword ToVu(qword a)
{
    qword b;
    __asm__("qmtc2 %1,%0":"=j"(b):"r"(a));
    return b;
}
static inline qword Sub(qword a,qword b)
{
    qword d;
    __asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));
    return d;
}
static inline float LenSq(qword a)
{
    qword d,one;
    float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(d));
    return f;
}
// name: SafeHouse port (FPickupTouched)
int FPickupTouched__FP2LOP6PICKUP(struct S *p,struct Q *q)
{
    char scratch[0x30] __attribute__((aligned(16)));
    qword pos;
    int i;
    float distance,maximum;
    if(!q->enabled||!q->so)return 0;
    pos=ToVu(PosOfLo__FP2LO(p));
    distance=LenSq(Sub(pos,PosOfLo__FP2LO(q->so)));
    maximum=D_002C0D7C;
    if(maximum*maximum<distance)return 0;
    if(distance<q->radius*q->radius) {
        Trigger(p);
        return 1;
    }
    for(i=0;i<q->so->count;i++) {
        struct SHAPE *s=&q->so->shapes[i];
        if(s->flags&(1UL<<50))continue;
        if(s->flags&(1UL<<49)) {
            float r=p->radius+s->radius;
            qword here=PosOfLo__FP2LO(p);
            if(LenSq(Sub(here,s->pos->pos))<r*r) {
                Trigger(p);
                return 1;
            }
        } else {
            qword here=PosOfLo__FP2LO(p);
            if(SphereBspContacts__FG9VU_VECTORfP6SOPARTP3BSPiT3iP9CMCONTACT(here,s,0x7FFFFFFF,0,0,1,scratch,p->radius)) {
                Trigger(p);
                return 1;
            }
        }
    }
    return 0;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
