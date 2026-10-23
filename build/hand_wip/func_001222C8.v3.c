/* v3 (Claude agent laneB8, 2026-10-23): aligned 10 -> 2. ONE commented register pin: pf in $2 (v0), plus the tail written as `pf += j; f(*pf)` in all three arms (the sum then reuses pf like the target). Left: 1B-else `sll v0,a1,4; lw a1,pv` (target puts i<<4 in pf/v0, pv in a1; ours sll a1 in place, pv in v0). Tried: (i<<4)+char*, int sums, pf = base + i*4, &[i].x, j pin instead, i pin: 2-18. */
/* v2 (Claude agent, 2026-10-17): aligned 22 -> 10. Shared function-scope i / j / float *pf across cases (pidx = pidx->pnext reused) gives the target t0/a1/a3 registers and the cross-jumped pf[j] tail. Left: pf in v1, j in v0 (target pf v0, j v1) in the pf[j] tail. */
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
    int i;
    int j;
    register float *pf __asm__("$2"); /* register pin: pf must be v0 (j gets v1) in the shared pf[j] tail */
    ref.m_tagk = -1;
    pidx = (IDX *)aref[1].u.pv;
    switch (aref[0].m_tagk) {
    case 0x1B: {
        i = pidx->i;
        if (carg == 2) {
            func_001296A8(&ref, &((VECTOR *)aref[0].u.pv)[i]);
        } else {
            pf = (float *)&((VECTOR *)aref[0].u.pv)[i];
            pidx = pidx->pnext;
            j = pidx->i;
            pf += j;
        func_00129558(&ref, *pf);
        }
        break;
    }
    case 0x1A: case 0x1C: case 0x1D:
        pf = (float *)aref[0].u.pv;
        j = pidx->i;
        pf += j;
        func_00129558(&ref, *pf);
        break;
    case 0x1E:
        pf = (float *)aref[0].u.pv;
        j = pidx->i;
        pf += j;
        func_00129558(&ref, *pf);
        break;
    }
    func_001291A8(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
