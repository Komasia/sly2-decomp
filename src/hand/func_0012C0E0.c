/* TRKPA::IkeyFind: the index of the key segment [i-1, i] whose times hold g. Layout: SafeHouse port (aseg.h). */
typedef struct TRKPA { int pvtbl; int ckey; float *at; } TRKPA;
// name: SafeHouse port (TRKPA::IkeyFind)
int IkeyFind__5TRKPAf(TRKPA *ptrk, float g)
{
    int ikey;
    for (ikey = 1; ikey < ptrk->ckey - 1; ikey++) {
        if (g < ptrk->at[ikey])
            break;
    }
    return ikey;
}
