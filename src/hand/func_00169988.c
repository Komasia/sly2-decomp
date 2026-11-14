/* A qsort-style comparator of 0x14-byte records (no direct callers): by +0x4 (in 0x40-byte units), then +0x8, then
 * +0xC (in 0x40-byte units), then +0x10. */
typedef struct REC40 { char ab[0x40]; } REC40;
typedef struct KEY {
    /* 0x00 */ int n0;
    /* 0x04 */ REC40 *prec4;
    /* 0x08 */ int n8;
    /* 0x0c */ REC40 *precC;
    /* 0x10 */ int n10;
} KEY;

int func_00169988(KEY *pkey0, KEY *pkey1)
{
    int d = pkey0->prec4 - pkey1->prec4;

    if (d == 0) {
        d = pkey0->n8 - pkey1->n8;
        if (d == 0) {
            d = pkey0->precC - pkey1->precC;
            if (d == 0) {
                return pkey0->n10 - pkey1->n10;
            }
        }
    }
    return d;
}
