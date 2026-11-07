struct S { char pad[0x38]; float g; char p2[0xA4]; void *pe0; };
extern float D_002BE8C8;
void PostLoLoad__FP2LO(struct S *p);
void SetZoneForced__FP2LOi(void *p, int n);
void func_00183768(struct S *p)
{
    PostLoLoad__FP2LO(p);
    if (p->pe0) SetZoneForced__FP2LOi(p->pe0, 0);
    if (p->g == 1e10f) p->g = D_002BE8C8;
}
