struct S { char pad[0x190]; char sub[0x2C]; int n; };
void func_001E5D80(struct S *p);
void func_00182C70(void *p);
void func_00182E80(struct S *p)
{
    func_001E5D80(p);
    func_00182C70(p->sub);
    p->n = 3;
}
