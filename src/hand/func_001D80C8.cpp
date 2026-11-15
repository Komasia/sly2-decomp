/* FSetProgress (SafeHouse savedata.h, orig 0x1D80C8): write a value at the path in the save pbSave, converted to
 * the node's kind (a bool of an indexed node sets / clears one bit); nothing when the path does not resolve to a
 * value. Returns a Void CRef. */
#define TAGK_Void 0x24
struct QW16 { int a[4]; } __attribute__((aligned(16)));
struct V2 { int a[2]; };
struct V3 { int a[3]; };
struct CRef {
    int m_tagk;
    union { int m_tag; float m_g; void *m_pv; };
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    void InitTag(int);
    void Decref();
};
#include "h3_progress.h"
extern "C" int FFindEntryKey(LAYOUT *playout, KEY *pkey, PENTFOUND *pfound) asm("FFindEntryKey__FP4TRIEPP4PENTPi");
// name: SafeHouse port (FSetProgress)
extern "C" CRef FSetProgress__FP4TRIEP4CRefT1Pc(LAYOUT *playout, KEY *pkey, const CRef &val, char *pbSave)
{
    CRef ref(TAGK_Void);
    PENTFOUND found;
    PENT *pent;
    if (!FFindEntryKey(playout, pkey, &found) || (pent = found.pent)->kind == PROGK_Node)
        return ref;
    {
        unsigned char *pv = (unsigned char *)pbSave + pent->ib;
        switch (pent->kind) {
        case PROGK_S32:
        case PROGK_S32_1:
        case PROGK_S32_2:
        case PROGK_S32_9:
        case PROGK_S32_10:
            ((int *)pv)[found.i] = val.m_tag;
            break;
        case PROGK_F32:
            ((float *)pv)[found.i] = val.m_g;
            break;
        case PROGK_Bool:
            if (pent->fIndexed) {
                int ibit = found.i;
                unsigned char b;
                pv += ibit / 8;
                b = 1 << (ibit % 8);
                if (val.m_tag)
                    *pv |= b;
                else
                    *pv &= ~b;
            } else {
                *(int *)pv = val.m_tag;
            }
            break;
        case PROGK_Vector:
        case PROGK_S32x4:
            ((QW16 *)pv)[found.i] = *(QW16 *)val.m_pv;
            break;
        case PROGK_S32x2:
            ((V2 *)pv)[found.i] = *(V2 *)val.m_pv;
            break;
        case PROGK_S32x3:
            ((V3 *)pv)[found.i] = *(V3 *)val.m_pv;
            break;
        }
    }
    return ref;
}
