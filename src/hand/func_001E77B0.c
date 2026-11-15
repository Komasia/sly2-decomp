/* func_001E77B0: the point of a curve nearest pos (NearestCrvAll over the whole curve). pos is declared
 * int: the caller's 128-bit position register is passed on as it is. */
typedef int qword __attribute__((mode(TI)));
struct CRV;
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct CRV *pcrv, int pos, int pcnstr, qword *pposNearest, int pdir, int pg, int ps);
qword func_001E77B0(struct CRV *pcrv, int pos)
{
    qword posNearest;
    NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(pcrv, pos, 0, &posNearest, 0, 0, 0);
    return posNearest;
}
