struct S4 { char a[4]; };
struct CM { char pad[0x24C]; struct S4 s; };
void AdjustRgba__FPUi(void *p);
void RecalcCmFrustrum__FP2CM(struct CM *p);
void SetCmRgbaFog__FP2CMP4RGBA(struct CM *p, struct S4 *s)
{
    p->s = *s;
    AdjustRgba__FPUi(&p->s);
    RecalcCmFrustrum__FP2CM(p);
}
