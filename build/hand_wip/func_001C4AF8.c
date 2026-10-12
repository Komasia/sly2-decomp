typedef int qword __attribute__((mode(TI)));
struct LO { char pad[0x28]; unsigned long x28; };
struct G { char pad[0x3EB8]; int c; struct LO *a[1]; };
extern float D_002A7708;
qword func_001A62E8(struct LO *plo);
static inline float DistSq(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %1, %1" : "=j"(d) : "j"(d));
    __asm__ volatile("vaddw.x %0, $vf0, $vf0w" : "=j"(one));
    __asm__("vadday.x $ACC, %1, %1y\n\tvmaddz.x %0, %2, %1z" : "=j"(d) : "j"(d), "j"(one));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
struct LO *func_001C4AF8(struct G *p, qword pos)
{
    struct LO *ploBest = 0;
    float dBest = D_002A7708;
    int i;
    for (i = 0; i < p->c; i++) {
        struct LO *plo = p->a[i];
        if ((int)(plo->x28 >> 60) & 1) {
            float f = DistSq(pos, func_001A62E8(plo));
            if (f < dBest) {
                dBest = f;
                ploBest = plo;
            }
        }
    }
    return ploBest;
}
