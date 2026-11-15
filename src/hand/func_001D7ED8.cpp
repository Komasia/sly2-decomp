/* RefGetProgress (SafeHouse savedata.h, orig 0x1D7ED8): the progress value a path names in the save pbSave, as a
 * CRef of its kind (int, float, bool - one bit of a bit set when indexed -, vector or int tuple); Nil (a default
 * CRef) when the path does not resolve to a value. */
struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
struct QW16 { int a[4]; } __attribute__((aligned(16)));
struct V2 { int a[2]; };
struct V3 { int a[3]; };
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(int);
    CRef &operator=(float);
    CRef &operator=(bool);
    CRef &operator=(const VECTOR &);
    CRef &operator=(const QW16 &);
    CRef &operator=(const V2 &);
    CRef &operator=(const V3 &);
    void Decref();
};
#include "h3_progress.h"
extern "C" int FFindEntryKey(LAYOUT *playout, KEY *pkey, PENTFOUND *pfound) asm("FFindEntryKey__FP4TRIEPP4PENTPi");
// name: SafeHouse port (RefGetProgress)
extern "C" CRef RefGetProgress__FP4TRIEP3KEYPc(LAYOUT *playout, KEY *pkey, char *pbSave)
{
    CRef ref;
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
        case PROGK_S32_10:
            ref = ((int *)pv)[found.i];
            break;
        case PROGK_F32:
            ref = ((float *)pv)[found.i];
            break;
        case PROGK_Bool:
            if (pent->fIndexed) {
                int ibit = found.i;
                unsigned char b;
                pv += ibit / 8;
                b = 1 << (ibit % 8);
                ref = (bool)((*pv & b) != 0);
            } else {
                ref = *(bool *)pv;
            }
            break;
        case PROGK_Vector:
            ref = ((VECTOR *)pv)[found.i];
            break;
        case PROGK_S32x4:
            ref = ((QW16 *)pv)[found.i];
            break;
        case PROGK_S32x2:
            ref = ((V2 *)pv)[found.i];
            break;
        case PROGK_S32x3:
            ref = ((V3 *)pv)[found.i];
            break;
        case PROGK_S32_9:
            ref = ((int *)pv)[found.i];
            break;
        }
    }
    return ref;
}
