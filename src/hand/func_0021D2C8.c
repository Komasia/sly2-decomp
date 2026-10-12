struct S { char pad[0x38]; float x38; char pad2[0xB0]; float xec; };
void func_001A5C48(struct S *p);
extern float D_002C40C0;
void func_0021D2C8(struct S *p)
{
    func_001A5C48(p);
    if (p->x38 == 1e10f)
        p->x38 = p->xec + D_002C40C0;
}
