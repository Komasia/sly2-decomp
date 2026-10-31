typedef struct MSG { int cb; int nKind; } MSG;
void *PvAllocSwClearImpl__Fi(MSG *pmsg);
static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwClearImpl__Fi(pmsg); }
struct C { int a[4]; };
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; int pad[6]; unsigned long fl; };
struct DA { int n0; int cMax; int c; struct O **a; };
struct S { char pad[0xE0]; int c; struct O **apo; };
void __10STACKSCOPE(struct C *);
void _$_10STACKSCOPE(struct C *, int);
void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(struct S *p, void *q);
void func_0013F888(struct DA *pda);
void func_002317E0(struct S *p, void *q, struct DA *pda);
int func_00132B10(void *p, int n);
void LoadExplgFromBrx__FP5EXPLGP18CBinaryInputStream(struct S *p, void *q)
{
    struct C ctx;
    struct DA da;
    MSG msg;
    int i;
    LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(p, q);
    __10STACKSCOPE(&ctx);
    func_0013F888(&da);
    func_002317E0(p, q, &da);
    p->apo = PvAllocMsg(&msg, da.c * 4, 0x10);
    for (i = 0; i < da.c; i++) {
        struct O *o = da.a[i];
        o->fl |= 0x200000000000000L;
        if (!func_00132B10(o, 0x1E)) {
            struct VTE *e = &o->vt[9];
            e->pfn((char *)o + e->d);
        } else {
            p->apo[p->c++] = o;
        }
    }
    _$_10STACKSCOPE(&ctx, 2);
}
