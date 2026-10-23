struct R { float g; int n; float g8; };
struct S { char pad[0x40]; unsigned int fl; char pad2[0x14]; float g58; float g5C; char pad3[0x234 - 0x60];
    float g234; float g238; char pad4[0x280 - 0x23C]; int n280; char pad5[8]; struct R r; float g298; float g29C; float g2A0; float g2A4; };
extern struct S *D_002DE570;
void func_001A5270(struct S *p);
void func_001A6CA8(struct S *p, int n);
static inline float GAbs(float g) { return g < 0.0f ? -g : g; }
void func_001526D8(struct S *p)
{
    unsigned int v;
    struct R *pr;
    func_001A5270(p);
    D_002DE570 = p;
    p->g234 = -1.5f;
    p->g238 = 1.0f;
    p->g5C = 0.4f;
    p->n280 = 8;
    p->g58 = 0.4f;
    pr = &p->r;
    {
        float gMax = p->g238, gMin = p->g234;
        __asm__("" : "+f"(gMin)); /* emulates the original compiler not folding float constants */
        pr->g = __builtin_fabsf(gMax - gMin) * 0.33333334f;
    }
    pr->g8 = 5.0f;
    pr->n = 0;
    p->g29C = -0.8f;
    p->g2A0 = -0.2f;
    p->g2A4 = -1.5f;
    p->g298 = -1.5f;
    func_001A6CA8(p, 1);
    v = p->fl;
    if ((v ^ 1) & 1) *(int *)v |= 0xA;
    else p->fl = v | 0xA;
}
