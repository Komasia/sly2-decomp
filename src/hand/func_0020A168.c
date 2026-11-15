typedef int qword __attribute__((mode(TI)));
struct NOISETMPL { char pad[0x50]; int nType; };   /* its perception type */
/* a noise: its template, place, time and kind (SafeHouse ainoise.h) */
struct NOISE { char pad[0x14]; struct NOISETMPL *ptmpl; char pad2[0x20 - 0x18]; qword pos; char pad3[0x4C - 0x30]; float t; char pad4[4]; int nKind; char pad5[0x60 - 0x58]; };
qword PosOfLo__FP2LO(void *plo);

/* the squared distance of plo from *ppos */
static inline float DistSq(void *plo, qword *ppos)
{
    qword pos = PosOfLo__FP2LO(plo), d, r, t;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(*ppos));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(t) : "0"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(r));
    return f;
}

/* NCompareNoises (0x20A168): orders two noises for the guard: by perception type, then the higher kind, the newer,
 * the nearer, then their order in memory. */
// name: SafeHouse port (NCompareNoises)
int NCompareNoises__FP5GUARDP5NOISET1(void *pguard, struct NOISE *pnoiseA, struct NOISE *pnoiseB)
{
    int dn;
    float dsA, dsB;
    dn = pnoiseA->ptmpl->nType - pnoiseB->ptmpl->nType;
    if (dn)
        return dn;
    dn = pnoiseB->nKind - pnoiseA->nKind;
    if (dn)
        return dn;
    if (pnoiseA->t > pnoiseB->t)
        return -1;
    if (pnoiseA->t < pnoiseB->t)
        return 1;
    dsA = DistSq(pguard, &pnoiseA->pos);
    dsB = DistSq(pguard, &pnoiseB->pos);
    if (dsA < dsB)
        return -1;
    if (dsB > dsA)
        return 1;
    return pnoiseA - pnoiseB;
}
