/* TRKPK::Eval (two-tangent keys): the track's position / velocity at g: Hermite over the key segment around g
 * (start: key i-1's pos and out tangent, end: key i's pos and in tangent). Layout: SafeHouse port (aseg.h). */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEYP { VECTOR3 pos; float t; qword vIn; qword vOut; } KEYP;   /* field: SafeHouse port */
typedef struct TRKPK { int pvtbl; int ckey; KEYP *akey; } TRKPK;
int IkeyFind__5TRKPKf(TRKPK *ptrk, float g);
void Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(float tMax, float t, float s, qword a, qword va, qword b, qword vb, void *ppos, void *pv, int n);
// name: SafeHouse port (TRKPK::Eval)
void Eval__5TRKPKP7VECTOR4T1ff(TRKPK *ptrk, void *ppos, void *pvel, float g, float dtScale)
{
    int ikey = IkeyFind__5TRKPKf(ptrk, g);
    V3Q pos0, pos1;
    pos0.v = ptrk->akey[ikey - 1].pos;
    pos1.v = ptrk->akey[ikey].pos;
    /* key i-1's vOut is the quadword just before key i */
    Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(ptrk->akey[ikey].t - ptrk->akey[ikey - 1].t, g - ptrk->akey[ikey - 1].t, dtScale, pos0.q, *(qword *)((char *)&ptrk->akey[ikey] - 0x10), pos1.q, ptrk->akey[ikey].vIn, ppos, pvel, 0);
}
