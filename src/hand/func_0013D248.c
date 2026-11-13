struct C { int a[4]; };
struct CRef { int m_tagk; int m_n; };
struct S { char pad[0x184]; int f184; };
extern char D_003D4A60[];
void __10STACKSCOPE(struct C *);
void _$_10STACKSCOPE(struct C *, int);
void *AkeyStand__FP2LO(struct S *);
void NProgress(struct CRef *, void *, void *);
void Decref(struct CRef *) asm("Decref__4CRef");
static inline int NFromRef(void *pv)
{
    struct CRef ref;
    int n;
    NProgress(&ref, pv, D_003D4A60);
    n = ref.m_n;
    Decref(&ref);
    return n;
}
// name: SafeHouse port (IdStandSaved)
int IdStandSaved__FP2LO(struct S *p) {
    struct C ctx;
    int n;
    __10STACKSCOPE(&ctx);
    n = NFromRef(AkeyStand__FP2LO(p));
    if (n == 0) n = p->f184;
    else if (n >= 0) { if (n < 10) { if (n >= 7) n = -1; } }
    switch (n) {
    case 0x2bf: n = 0x2bc; break;
    case 0x2c0: n = 0x2bd; break;
    case 0x2c1: n = 0x2be; break;
    }
    _$_10STACKSCOPE(&ctx, 2);
    return n;
}
