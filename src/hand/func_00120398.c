/* RefCmp: compares two numeric references (ints converted to float) by op (enum CMPK) into a bool. */
#include "splice.h"
CRef *RefCmp__FP4CRef4CMPK(CRef *ret, CRef *aref, int op)
{
    float ag[2];
    int i;
    int f;
    for (i = 0; i < 2; i++) {
        if (aref[i].m_tagk == TAGK_F32)
            ag[i] = aref[i].m_tag.m_g;
        else
            ag[i] = (float)aref[i].m_tag.m_n;
    }
    switch (op) {
    case CMPK_L:
        f = ag[0] < ag[1];
        break;
    case CMPK_LE:
        f = ag[0] <= ag[1];
        break;
    case CMPK_G:
        f = ag[0] > ag[1];
        break;
    case CMPK_GE:
        f = ag[0] >= ag[1];
        break;
    }
    ret->m_tag.m_bool = f;
    ret->m_tagk = TAGK_Bool;
    return ret;
}
