/* BIF vector-dot-product. */
#include "splice.h"
static __inline__ int GDot(qword *pa, qword *pb)
{
    register qword a __asm__("vf1") = *pa;
    register qword b __asm__("vf2") = *pb;
    register qword t __asm__("vf3");
    int g;
    __asm__ ("vmul.xyz %0, %0, %2\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(a), "=j"(t) : "j"(b));
    __asm__ ("qmfc2.ni %0, %1" : "=r"(g) : "j"(a));
    return g;
}
CRef *RefOpVectorDotProduct__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int g = GDot((qword *)aref[0].m_tag.m_pv, (qword *)aref[1].m_tag.m_pv);
    ret->m_tagk = TAGK_F32;
    *(volatile int *)&ret->m_tag.m_n = g;
    return ret;
}
