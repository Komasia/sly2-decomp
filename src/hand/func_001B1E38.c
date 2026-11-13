struct S { char pad[0x234]; int x; char pad2[0x268 - 0x238]; char y[4]; };
void OnSoRemove__FP2SO(struct S *p);
void ApplyAsegCur(int a, struct S *b, int c, void *d, float f, float g) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void DeleteCtrl__FPP4CTRL(void *p);
void OnMissileRemove__FP7MISSILE(struct S *p)
{
    OnSoRemove__FP2SO(p);
    ApplyAsegCur(0, p, 0, &p->x, 0.0f, 1.0f);
    DeleteCtrl__FPP4CTRL(p->y);
}
