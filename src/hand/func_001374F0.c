/* SelectSlyDodgeSide: the side of a new dodge: with the stick pushed and an object faced, 0 when the object lies to
 * the stick's right (the stick direction turned by -90 degrees, dotted with the offset to the object), else 1;
 * otherwise the last side. Layout: SafeHouse port (sly.cpp). */
typedef int qword __attribute__((mode(TI)));
struct PADCTL { char pad[0x18]; float radStick; float uStick; };
struct SLY { char pad[0x150]; struct PADCTL *ppadctl; char pad2[0x10DC - 0x154]; void *ploFace; };
struct SLYDODGE { struct SLY *psly; int state; int tState; int stateLast; };
qword SetVectorCylind__Ffff(float a, float b, float c);
qword PosOfLo__FP2LO(void *plo);
// name: SafeHouse port (SelectSlyDodgeSide)
int SelectSlyDodgeSide__FP3SLY(struct SLYDODGE *pdodge)
{
    float zero = 0.0f;
    struct PADCTL *ppadctl = pdodge->psly->ppadctl;
    if (zero < ppadctl->uStick && pdodge->psly->ploFace) {
        qword v = SetVectorCylind__Ffff(ppadctl->radStick - 1.5707964f, 1.0f, zero);
        qword a = PosOfLo__FP2LO(pdodge->psly->ploFace);
        qword b, d, t;
        float g;
        __asm__("" : "+j"(a));
        b = PosOfLo__FP2LO(pdodge->psly);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xyz %0, %2, %3\n"
            "vaddw.x %1, $vf0, $vf0w\n"
            "vadday.x ACC, %0, %0y\n"
            "vmaddz.x %0, %1, %0z" : "=j"(d), "=j"(t) : "j"(v), "j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
        if (g > zero) return 0; return 1;
    }
    return pdodge->stateLast;
}
