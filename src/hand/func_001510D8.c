struct S { int pad[6]; float g18; char pad2[0xAC - 0x1C]; float gAC; };
int FFloatsNear(float a, float b, float eps) asm("FFloatsNear__Ffff");
int func_001510D8(struct S *p)
{
    int f = 0;
    if (p->g18 < 0.0f || FFloatsNear(p->gAC, p->g18, 0.01f))
        f = 1;
    return f;
}
