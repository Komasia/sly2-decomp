/* TRKPA::IkeyFind for kind-4 tracks: the index of the key segment [i-1, i] whose times hold g. */
typedef struct TRKPA { int pvtbl; int ckey; float *at; } TRKPA;
int func_0012C708(TRKPA *ptrk, float g)
{
    int ikey;
    for (ikey = 1; ikey < ptrk->ckey - 1; ikey++) {
        if (g < ptrk->at[ikey])
            break;
    }
    return ikey;
}
