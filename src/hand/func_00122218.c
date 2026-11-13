typedef struct CRef { int m_tagk; union { int n; float g; void *pv; } u; } CRef;
void Decref__4CRef(CRef *pref);
void InitTag__4CRef(CRef *pref, int tagk);
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
CRef *RefOpSmp__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    int i;
    float *pg;
    InitTag__4CRef(&ref, 0x1E);
    pg = (float *)ref.u.pv;
    for (i = 0; i < 3; i++) {
        CRef tmp;
        RefCoerceF32__4CRef(&tmp, &aref[i]);
        pg[i] = tmp.u.g;
        Decref__4CRef(&tmp);
    }
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
