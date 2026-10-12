struct S { char pad[0x164]; void *x; char y[4]; };
void func_001F2C30(struct S *p);
void func_001F1448(void *a, struct S *p, int b, int c, void *d);
void func_00224028(struct S *p)
{
    func_001F2C30(p);
    if (p->x) func_001F1448(p->x, p, -1, 0, p->y);
}
