/* C++ view of the Splice reference CRef, for the C++ sources (script-method thunks, BIFs) that pass and return
 * CRef by value. The C sources use include/splice.h's plain struct instead; don't include both.
 *
 * Every method except the default constructor, CRef(int) and the destructor is out of line (in the splice ref
 * module, 0x1291A8..0x12A0B0); declaring them here emits nothing. The thunks' common shape:
 *     CRef ref = RefSetArgsFromSplice(carg, aref, aotype, &arg0, ...);   // type-check and unpack the arguments
 *     ref.Decref(); ref.InitTag(TAGK_Void);                              // a method without a result
 *     DoTheThing(plo, arg0, ...);
 *     return ref;
 */
#ifndef SPLICE_CREF_H
#define SPLICE_CREF_H

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

#ifndef SPLICE_H
/* tag kinds (same values as include/splice.h's enum TAGK) */
enum TAGK {
    TAGK_Nil = -1,      /* the default-constructed (unset) reference */
    TAGK_None = 0,      /* the empty list */
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
#endif

/* Argument types for RefSetArgsFromSplice's OTYPE array (the ones SafeHouse's scpt.cpp identifies). Larger values
 * (0x1000 | n, 0x2000 | n, 0x9000 | n, ...) are typed objects / enumerations and stay numbers. */
enum OTYPE {
    OTYPE_Bool = 0,
    OTYPE_Float = 1,
    OTYPE_Vector = 2,     /* a VECTOR, passed as a G9VU_VECTOR qword */
    OTYPE_Int = 6,
    OTYPE_IntList = 0x8006
};

struct CRef {
    /* 0x0 */ int m_tagk;    /* enum TAGK */
    /* 0x4 */ union { int n; float g; void *pv; } u;
    CRef() { m_tagk = TAGK_Nil; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};

#endif
