/* TRKPK::IkeyFind: the index of the key segment [i-1, i] that holds the parameter g (keys searched from 1 up to
 * c-1, so the result is always a valid segment end). Layout: SafeHouse port (aseg.h TRKPK / KEYP). */
typedef struct KEYP {
    /* 0x00 */ int pos[3];      /* field: SafeHouse port */
    /* 0x0c */ float t;         /* field: SafeHouse port - the key's time */
    /* 0x10 */ int vIn[4];      /* field: SafeHouse port - the tangent in */
    /* 0x20 */ int vOut[4];     /* field: SafeHouse port - the tangent out */
} KEYP;
typedef struct TRKPK {
    /* 0x00 */ int pvtbl;
    /* 0x04 */ int ckey;
    /* 0x08 */ KEYP *akey;      /* field: SafeHouse port */
} TRKPK;
// name: SafeHouse port (TRKPK::IkeyFind)
int IkeyFind__5TRKPKf(TRKPK *ptrk, float g)
{
    int ikey;
    for (ikey = 1; ikey < ptrk->ckey - 1; ikey++) {
        if (g < ptrk->akey[ikey].t)
            break;
    }
    return ikey;
}
