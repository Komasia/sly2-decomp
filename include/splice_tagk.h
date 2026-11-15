/* Splice tag kinds (CRef::m_tagk), for C++ sources that declare their own CRef class. Same values as
 * include/splice.h's enum TAGK, plus the special-form tags 1..20 that the evaluator dispatches on (names and
 * numbering: SafeHouse ref.h; evidence Eval 0x127838, the list loader 0x12A3D8, EvalLambda 0x127068). */
#ifndef SPLICE_TAGK_H
#define SPLICE_TAGK_H
#ifndef SPLICE_H
enum TAGK {
    TAGK_Nil = -1,      /* the default-constructed (unset) reference */
    TAGK_None = 0,      /* the empty list */
    TAGK_Set = 1,       /* (set! sym expr) */
    TAGK_Define = 2,    /* (define sym expr) */
    TAGK_DefineMacro = 3,
    TAGK_DefineMacroLambda = 4,
    TAGK_Assert = 5,
    TAGK_Debug = 6,     /* new in Sly 2 */
    TAGK_If = 7,
    TAGK_Or = 8,
    TAGK_And = 9,
    TAGK_Cond = 0xA,
    TAGK_Else = 0xB,
    TAGK_Case = 0xC,
    TAGK_Let = 0xD,
    TAGK_While = 0xE,
    TAGK_Lambda = 0xF,
    TAGK_Begin = 0x10,
    TAGK_Import = 0x11,
    TAGK_Quote = 0x12,
    TAGK_Pipe = 0x13,   /* name from Sly 1's order, unconfirmed */
    TAGK_Dot = 0x14,    /* the rest-parameter marker in a lambda's formals */
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
    TAGK_Err = 0x23,    /* unconfirmed */
    TAGK_Void = 0x24
};
#endif
#endif
