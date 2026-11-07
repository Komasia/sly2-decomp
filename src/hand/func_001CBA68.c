struct S { char pad[0xE4]; int ne4; };
float SMinCrv__FP3CRV(struct S *p);
float SMaxCrv__FP3CRV(struct S *p);
int func_001CBA68(struct S *p, float *pg)
{
    /*B*/if (p->ne4) { pg[0] = SMinCrv__FP3CRV(p); pg[1] = SMaxCrv__FP3CRV(p); return 1; } return 0;/*E*/
}
