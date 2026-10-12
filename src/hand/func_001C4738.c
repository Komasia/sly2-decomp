struct S { char pad[0x88]; float a[32]; };
void func_001C4738(struct S *p, int grf)
{
    float *pg;
    if (!grf) return;
    pg = p->a;
    do { if (grf & 1) *pg = -3.40282346638528859812e+38f; grf >>= 1; pg++; } while (grf);
}
