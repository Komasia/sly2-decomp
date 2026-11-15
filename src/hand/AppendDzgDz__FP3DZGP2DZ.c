/* AppendDzgDz: adds a row to a constraint system's open list, filling the new column of every row whose
 * couplings are already computed: the row's normal dotted with that row's response to the new contact. */
#include "dzg.h"
struct XP { char pad[0xA8]; int ixp; };   /* +0xA8: the contact's index in the system */
extern void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
static __inline__ int Dot(qword a, qword b)
{
    qword r, one;
    int g;
    __asm__("vmul.xyz %0, %0, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(one) : "0"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
void AppendDzgDz(DZG *pdzg, DZ *pdz, DZENT *pent) __asm__("AppendDzgDz__FP3DZGP2DZ");
void AppendDzgDz(DZG *pdzg, DZ *pdz, DZENT *pent)
{
    int i;
    int ixp = pent->pxp->ixp;
    for (i = 0; i < pdzg->cdz; i++) {
        DZ *pdzI = &pdzg->adz[i];
        int *agCoupling = (int *)pdzI->agCoupling;
        if (agCoupling) {
            __asm__ __volatile__("" ::: "memory");
            {
                DZENT *pentI = &pdzg->aent[i];
                agCoupling[pdzg->cdz] = Dot(pent->normal, pentI->aresp[ixp]);
            }
        }
    }
    AppendDlEntry__FP2DLPv(&pdzg->dlOpen, pdz);
    pdzg->cdz++;
}
