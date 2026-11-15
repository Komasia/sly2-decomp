/* TRKPK::Eval for one-tangent keys: Hermite over the key segment around g. Layout: SafeHouse port (aseg.h). */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEYP1 { VECTOR3 pos; float t; qword v; } KEYP1;
typedef struct TRKPK { int pvtbl; int ckey; KEYP1 *akey; } TRKPK;
int func_0012BB70(TRKPK *ptrk, float g);
void Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(float tMax, float t, float s, qword a, qword va, qword b, qword vb, void *ppos, void *pv, int n);
void func_0012BE68(TRKPK *ptrk, void *ppos, void *pvel, float g, float dtScale)
{
    int ikey = func_0012BB70(ptrk, g);
    V3Q pos0, pos1;
    pos0.v = ptrk->akey[ikey - 1].pos;
    pos1.v = ptrk->akey[ikey].pos;
    /* key i-1's tangent is the quadword just before key i */
    Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(ptrk->akey[ikey].t - ptrk->akey[ikey - 1].t, g - ptrk->akey[ikey - 1].t, dtScale, pos0.q, *(qword *)((char *)&ptrk->akey[ikey] - 0x10), pos1.q, ptrk->akey[ikey].v, ppos, pvel, 0);
}
