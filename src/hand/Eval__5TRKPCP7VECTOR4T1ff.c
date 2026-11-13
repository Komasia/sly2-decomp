/* TRKPC::Eval: a constant position track: the position is its point (+0x4) and the velocity is zero.
 * Layout: SafeHouse port (aseg.h TRKPC). */
struct VECTOR3 { float x, y, z; };
struct TRKPC {
    /* 0x0 */ void *pvtbl;
    /* 0x4 */ struct VECTOR3 pos;   /* field: SafeHouse port */
};
void CopyAb__FPvT0Ui(void *pvDst, void *pvSrc, unsigned int cb);

// name: SafeHouse port (TRKPC::Eval)
void Eval__5TRKPCP7VECTOR4T1ff(struct TRKPC *ptrk, struct VECTOR3 *ppos, struct VECTOR3 *pvel)
{
    if (ppos != 0)
        CopyAb__FPvT0Ui(ppos, &ptrk->pos, sizeof(struct VECTOR3));
    if (pvel != 0) {
        pvel->z = 0;
        pvel->y = 0;
        pvel->x = 0;
    }
}
