/* EvalCrvS: a curve's point and direction at a distance s along it (EvalCrv at the parameter of s). */
struct CRV;
struct VECTOR;
float GFromCrvS__FP3CRVf(struct CRV *pcrv, float s);
void EvalCrv__FP3CRVfP6VECTORT2(struct CRV *pcrv, float g, struct VECTOR *ppos, struct VECTOR *pdir);

// name: SafeHouse port (EvalCrvS, crv.h)
void EvalCrvS__FP3CRVfP6VECTORT2(struct CRV *pcrv, float s, struct VECTOR *ppos, struct VECTOR *pdir)
{
    EvalCrv__FP3CRVfP6VECTORT2(pcrv, GFromCrvS__FP3CRVf(pcrv, s), ppos, pdir);
}
