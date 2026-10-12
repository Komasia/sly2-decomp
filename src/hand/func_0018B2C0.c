struct S { char pad[0x150]; void *p150; char p1[0xDAC]; int xf00; int xf04; char p2[0x18]; int xf20; char p3[0xE1C]; int x1d40; };
int func_001443D8(struct S *p);
int func_001C46C0(void *p, int n, float g);
void func_0019CCE8(void *p);
void func_0019D330(void *p);
void func_0018B2C0(struct S *p)
{
    if (func_001443D8(p)) {
        if (p->xf04 == 1 && !p->xf20 &&
            func_001C46C0(p->p150, p->x1d40 == 7 ? 0x410 : 0x4F0, 0.25f))
            func_0019CCE8(&p->xf00);
        func_0019D330(&p->xf00);
    }
}
