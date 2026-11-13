struct S { char pad[0x1C4]; int x; };
void OnSoRemove__FP2SO(struct S *p);
void ApplyAsegCur(int a, int b, int c, void *d, float f, float g) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void func_001B0C68(struct S *p)
{
    OnSoRemove__FP2SO(p);
    ApplyAsegCur(0, 0, 0, &p->x, 0.0f, 0.0f);
}
