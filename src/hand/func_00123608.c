typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
void Decref__4CRef(CRef *pref);
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
int FCheckLm(int n, float g) asm("FCheckLm__FP2LMf");
CRef *RefOpLmCheck__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    int n = aref[0].u.n;
    CRef ref;
    int f;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    f = FCheckLm(n, ref.u.g) != 0;
    ret->m_tagk = 0x17;
    ret->u.n = f;
    Decref__4CRef(&ref);
    return ret;
}
