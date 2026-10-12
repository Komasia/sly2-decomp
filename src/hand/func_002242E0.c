struct S { char pad[0x150]; int k; };
void *func_001F4FC8(struct S *p, void *q);
int func_00132B10(void *q, int a);
void *func_00134310(void *v, int a);
void *func_002242E0(struct S *p, void *q)
{
    void *v = func_001F4FC8(p, q);
    int k = p->k;
    if (k == 0 || k == 4) { if (func_00132B10(q, 0x34)) v = func_00134310(v, 1); }
    return v;
}
