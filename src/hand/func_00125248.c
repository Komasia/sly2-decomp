typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *p, int n, float g);
extern char g_joy[];
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 130: TriggerJoyRumbleRumk on the pad)
CRef *RefOpStartRumble__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    void *p = g_joy;
    int n = aref[0].u.n;
    CRef ref;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    TriggerJoyRumbleRumk__FP3JOY4RUMKf(p, n, ref.u.g);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, 0x24);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
