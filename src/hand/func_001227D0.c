/* BIF vector-length. */
#include "splice.h"
static __inline__ int GLength(qword *pa)
{
    register qword a __asm__("vf1") = *pa;
    register qword t __asm__("vf2");
    int g;
    __asm__ ("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(a), "=j"(t));
    __asm__ ("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(a));
    __asm__ ("qmfc2.ni %0, %1" : "=r"(g) : "j"(a));
    return g;
}
CRef *RefOpVectorLth__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int g = GLength((qword *)aref[0].m_tag.m_pv);
    ret->m_tagk = TAGK_F32;
    *(volatile int *)&ret->m_tag.m_n = g;
    return ret;
}
