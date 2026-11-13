struct CRef { int m_tagk; float m_tag; };
struct B { char data[0x5464]; };
struct G { char pad[0x24]; struct B a[3]; char pad2[0xFD50 - 0x24 - 3 * 0x5464]; struct B *xFD50; int xFD54; struct B *xFD58; };
struct S { int x0, x4, x8; char pad[0x10]; int x1C; };
extern struct G D_002E65E0;
extern int D_003E0FAC;
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
void ResetSlotKeepSettings__FPci(struct B *b, int n);
void StartGameFromSave__FP2SW(struct B *b);
void func_001AD320(struct S *s)
{
    struct CRef ref;
    struct B *p = &D_002E65E0.a[s->x8];
    float f;
    NProgress(&ref, D_003E0FAC, p);
    f = ref.m_tag;
    Decref(&ref);
    D_002E65E0.xFD50 = p;
    if (f == 0.0f) {
        ResetSlotKeepSettings__FPci(p, 1);
        StartGameFromSave__FP2SW(D_002E65E0.xFD50);
    } else {
        StartGameFromSave__FP2SW(p);
        if (s)
            s->x1C |= 2;
    }
}
