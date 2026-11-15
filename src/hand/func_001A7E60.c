/* RecalcSwXpPos (0x1A7E60): updates contacts' end points from their objects' current transforms: a sphere end (end 0
 * of the kinds 4..6, end 1 of 7 / 9) is the sphere's center (XF +0x70) plus the normal times its radius (SOE +0x8,
 * negated for end 0), other ends their local point brought back to the world; then the separation along the normal
 * (gDist = (end0 - end1) . normal). SafeHouse so.cpp. */
#include "h5_xp.h"
struct SOE { int x0, x4; float sRadius; };
struct XF { char pad[0x70]; qword pos; };
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(struct XF *pxfFrom, struct XF *pxfTo, qword pos);
static __inline__ qword Lin(qword a, qword *pb, int f)
{
    union { qword q; float f; } t;
    __asm__("qmtc2.ni %1, %0" : "=j"(t.q) : "r"(f));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(a) : "0"(a), "j"(*pb), "j"(t.q):"memory");
    return a;
}
void RecalcSwXpPos__FP2SWiPP2XP(void *psw, int cpxp, struct XP **apxp)
{
    int i;
    for (i = 0; i < cpxp; i++) {
        struct XP *pxp = apxp[i];
        struct XPD *pxpd;
        int j;
        pxpd = pxp->axpd;
        for (j = 0; j < 2; j++, pxpd++) {
            struct XF *pxf = pxpd->pxf;
            if (!pxf)
                continue;
            {
            int f; qword position;
            union { float f; int i; } u;
            if (j == 0) {
                switch (pxp->xpk) {
                case 4: case 5: case 6:
                    u.f = -pxpd->psoe->sRadius; f = u.i; position=pxf->pos;
                    break;
                default:
                    goto def;
                }
            } else {
                switch (pxp->xpk) {
                case 7: case 9:
                    position=pxf->pos; f = *(int *)&pxpd->psoe->sRadius;
                    break;
                default:
                    goto def;
                }
            }
            pxpd->pos = Lin(position,&pxp->normal,f);
            continue;
            }
        def:
            pxpd->pos = PosConvertXfs__FP2XFT0G9VU_VECTOR(pxf, 0, pxpd->posLocal);
        }
        {
            qword d, r, one;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pxp->axpd[0].pos), "j"(pxp->axpd[1].pos));
            __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(one) : "j"(pxp->normal), "j"(d));
            { register float g __asm__("$4"); __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r)); __asm__("sw %1, %0" : "=m"(pxp->gDist) : "r"(g)); }
        }
    }
}
