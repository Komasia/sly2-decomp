/* TRKPK::IkeyFind for one-tangent (0x20-byte) keys: the index of the key segment [i-1, i] that holds g.
 * Layout: SafeHouse port (aseg.h). */
typedef struct KEYP1 { int pos[3]; float t; int v[4]; } KEYP1;
typedef struct TRKPK { int pvtbl; int ckey; KEYP1 *akey; } TRKPK;
int func_0012BB70(TRKPK *ptrk, float g)
{
    int ikey;
    for (ikey = 1; ikey < ptrk->ckey - 1; ikey++) {
        if (g < ptrk->akey[ikey].t)
            break;
    }
    return ikey;
}
