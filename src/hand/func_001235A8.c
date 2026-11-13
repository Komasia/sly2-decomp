typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
void Decref__4CRef(CRef *pref);
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
float GLimitLm(int n, float g) asm("GLimitLm__FP2LMf");
CRef *RefOpLmLimit__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    int n = aref[0].u.n;
    CRef ref;
    float g;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    g = GLimitLm(n, ref.u.g);
    ret->u.g = g;
    ret->m_tagk = 0x16;
    Decref__4CRef(&ref);
    return ret;
}
