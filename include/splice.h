/* Sly 2 Splice (the game's Scheme-like script language): references, pairs and the built-in functions (BIFs).
 * For C sources; the C++ ports in src/hand declare their own CRef classes.
 *
 * Names follow Sly 1's splice headers (ref.h, pair.h, bif.h). Sly 2 renumbered the tag kinds: the values below are
 * the ones Sly 2's type predicates test (RefOpIsBoolean .. RefOpIsProcedure, RefOpIsList / RefOpIsNull) and the
 * tags its BIFs set on their results. Sly 2's pairs carry a reference count before the Sly 1 fields.
 *
 * A BIF has the C++ signature  CRef RefOpXxx(int carg, CRef *aref, CFrame *pframe), which g++ 2.95 compiles as
 * CRef *RefOpXxx(CRef *pref, int carg, CRef *aref, CFrame *pframe)  (the result is built in *pref and returned);
 * the C definitions spell it that way, under the mangled name. g_mpbifkbif (0x2BBB90) is the {pfn, carg, fVarArgs}
 * table the evaluator dispatches through.
 */
#ifndef SPLICE_H
#define SPLICE_H
#include "mat.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

enum TAGK {
    TAGK_Nil = -1,      /* the default-constructed (unset) reference */
    TAGK_None = 0,      /* the empty list */
    /* 1 .. 20: special forms */
    TAGK_S32 = 0x15,
    TAGK_F32 = 0x16,
    TAGK_Bool = 0x17,
    TAGK_Symid = 0x18,
    TAGK_Bifk = 0x19,
    TAGK_Vector = 0x1A,
    TAGK_Matrix = 0x1B,
    TAGK_Clq = 0x1C,
    TAGK_Lm = 0x1D,
    TAGK_Smp = 0x1E,
    TAGK_Pair = 0x1F,
    TAGK_Proc = 0x20,
    TAGK_Basic = 0x21,
    TAGK_Method = 0x22,
    TAGK_Void = 0x24
};

enum CMPK { CMPK_L = 0, CMPK_LE = 1, CMPK_G = 2, CMPK_GE = 3 };

enum UFOK { UFOK_Sqrt = 0, UFOK_Sin = 1, UFOK_Cos = 2, UFOK_Tan = 3, UFOK_Asin = 4, UFOK_Acos = 5, UFOK_Atan = 6,
            UFOK_RadNormalize = 7 };

struct CPair;
struct CFrame;

typedef union TAG {
    int m_n;
    float m_g;
    int m_bool;
    unsigned int m_symid;
    struct CPair *m_ppair;
    struct VECTOR *m_pvector;
    struct MATRIX4 *m_pmatrix;
    void *m_pv;
    struct BASIC *m_pbasic;
} TAG;

typedef struct CRef {
    /* 0x0 */ int m_tagk;    /* enum TAGK */
    /* 0x4 */ TAG m_tag;
} CRef;

typedef struct CPair {
    /* 0x00 */ int cref;
    /* 0x04 */ int unk_0x4;
    /* 0x08 */ CRef m_ref;            /* car */
    /* 0x10 */ struct CPair *m_ppairNext;   /* cdr (0 at the end of a list) */
} CPair;

typedef struct CFrame CFrame;

/* CRef methods (C spellings of the g++ symbols) */
CRef *__4CRefRC4CRef(CRef *pref, const CRef *prefSrc);   /* 0x1291A8 copy constructor */
void Decref__4CRef(CRef *pref);                         /* 0x129EC8 (the inlined destructor) */
void InitTag__4CRef(CRef *pref, int tagk);              /* 0x12A0B0 sets the tag; allocates a VECTOR/MATRIX4/... for those kinds */

#endif
