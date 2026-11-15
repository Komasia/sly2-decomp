/* VU normalize + length; register vars pin the dead qmfc2 output and the pxf reloads */
/* CTRLSPIN::Start (kind 9, SafeHouse xf.cpp: orig 0x12E120): CTRL::Start, then the record spins about the job's
 * vector (+0x20): velocity = the vector, segment value 0 = its direction (D_002A2DA0 = x axis when it is ~0),
 * segment slope 0's x = its length (the speed in rad/s), value 1's x = 0. Layout: SafeHouse port (lo.h XF). */
typedef int qword __attribute__((mode(TI)));
typedef struct XF { char pad[0xB0]; qword vel; qword pos0; int gSpeed; /* aseg[1].x */ char pad2[0xE0 - 0xD4]; int gZero; } XF;
typedef struct CTRLSPIN { char pad[8]; XF *pxf; char pad2[0x20 - 0xC]; qword vec; } CTRLSPIN;
extern qword D_002A2DA0;
void Start__4CTRL(CTRLSPIN *pctrl);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    return l;
}
static __inline__ qword Normalize1(qword *pv, qword *pdef)
{
    qword c;
    qword l;   /* the vector's length */
    float gl;
    __asm__("qmtc2.ni %1, %0" : "=j"(c) : "r"(*pv));
    l = VLen(c);
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        *pv = *pdef;
    } else {
        qword rn;
        __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(rn) : "j"(c), "j"(l));
        *pv = rn;
    }
    return l;
}
void func_0012E120(CTRLSPIN *pctrl)
{
    qword l;   /* the vector's length */
    Start__4CTRL(pctrl);
    pctrl->pxf->vel = pctrl->vec;
    pctrl->pxf->pos0 = pctrl->vec;
    l = Normalize1(&pctrl->pxf->pos0, &D_002A2DA0);
    {
        register int n __asm__("$3");
        register XF *pxf __asm__("$2") = pctrl->pxf;
        __asm__("qmfc2.ni %0, %2\n\tsw %0, %1" : "=r"(n), "=m"(pxf->gSpeed) : "j"(l));
    }
    { register XF *pxf __asm__("$3") = pctrl->pxf; pxf->gZero = 0; }
}
