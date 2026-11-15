typedef int qword __attribute__((mode(TI)));
typedef struct CRef { int m_tagk; int m_tag; } CRef;
typedef struct MATRIX4 { qword a[4]; } MATRIX4;
void InitTag(CRef *pref, int tagk) asm("InitTag__4CRef");
void func_001A71B0(MATRIX4 *pmat, int a, int b, int c);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 127: a matrix from one object's space to another's)
CRef *RefOpConvertObjectMatrix__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    MATRIX4 mat;
    MATRIX4 *pmat;
    InitTag(&ref, 0x1B);
    pmat = (MATRIX4 *)ref.m_tag;
    func_001A71B0(&mat, aref[0].m_tag, aref[1].m_tag, aref[2].m_tag);
    *pmat = mat;
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
