struct S { char pad[0x15C]; int f; };
void OnSoAdd__FP2SO(struct S *p);
void func_0021BC08(struct S *p);
void func_0021BBD0(struct S *p)
{
    OnSoAdd__FP2SO(p);
    if (p->f)
        func_0021BC08(p);
}
