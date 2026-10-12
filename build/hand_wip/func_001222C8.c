typedef struct VECTOR { float x, y, z, w; } VECTOR;
typedef struct CRef { int m_tagk; union { int n; float g; void *pv; } u; } CRef;
typedef struct IDX { int pad[3]; int i; struct IDX *pnext; } IDX;
void Decref__4CRef(CRef *pref);
CRef *func_001291A8(CRef *pref, CRef *prefSrc);
CRef *func_00129558(CRef *pref, float g);
CRef *func_001296A8(CRef *pref, VECTOR *pv);
CRef *func_001222C8(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    IDX *pidx;
    ref.m_tagk = -1;
    pidx = (IDX *)aref[1].u.pv;
    switch (aref[0].m_tagk) {
    case 0x1B: {
        int i = pidx->i;
        if (carg == 2) {
            func_001296A8(&ref, &((VECTOR *)aref[0].u.pv)[i]);
        } else {
            func_00129558(&ref, ((float *)&((VECTOR *)aref[0].u.pv)[i])[pidx->pnext->i]);
        }
        break;
    }
    case 0x1A: case 0x1C: case 0x1D:
        func_00129558(&ref, ((float *)aref[0].u.pv)[pidx->i]);
        break;
    case 0x1E:
        func_00129558(&ref, ((float *)aref[0].u.pv)[pidx->i]);
        break;
    }
    func_001291A8(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
