struct VTE { short d; short pad; void *pfn; };
struct LO { int pad[3]; struct VTE *vt; };
struct X;
struct L { void *pv; struct L *pnext; struct L *pother; struct LO *po; };
struct LX { char pad[0xEC]; struct X *px; };
struct X { char pad[0x58]; struct X *pnext; int x5C; struct LO *plo; struct L *pl; void *pv68; int x6C; unsigned long grf; };
struct P { char pad[0x3D34]; struct X *pxFirst; };
struct C { int a[4]; };
void FlushSwOxaDirty1__FP2SW(struct P *p);
void UpdateSwAaox__FP2SW(struct P *p);
struct C *__10STACKSCOPE(struct C *);
void _$_10STACKSCOPE(struct C *, int);
void func_001A7E10(struct P *, void *);
void *PxpMarkOxaContacts__FP3OXAT0P2SO(struct P *, struct X *, struct X *);
void WakeAlo__FP3ALO(struct LO *);
void RemoveDlEntry__FP2DLPv(void *, struct X *);
#define VCALL(po, n, T) ((T)(po)->vt[n].pfn)((char *)(po) + (po)->vt[n].d
// name: SafeHouse port (UpdateSwXps)
void UpdateSwXps__FP2SW(struct P *p)
{
    struct C ctx;
    struct X *apx[0x300];
    int c = 0;
    struct X *px;
    int i;
    FlushSwOxaDirty1__FP2SW(p);
    UpdateSwAaox__FP2SW(p);
    __10STACKSCOPE(&ctx);
    for (px = p->pxFirst; px; px = px->pnext) {
        unsigned long grf = px->grf;
        struct L *pl;
        if (grf & 4)
            continue;
        grf |= 0x10;
        px->grf = grf;
        if (!(grf & 8)) {
            px->grf = grf | 8;
            apx[c++] = px;
        }
        for (pl = px->pl; pl; pl = pl->pnext) {
            struct X *px2 = ((struct LX *)pl->po)->px;
            unsigned long grf2 = px2->grf;
            void *pv;
            if (grf2 & 0x10)
                continue;
            if (grf2 & 4)
                continue;
            if (!(grf2 & 8)) {
                px2->grf = grf2 | 8;
                apx[c++] = px2;
            }
            VCALL(px->plo, 54, void (*)(void *, struct LO *)), px2->plo);
            VCALL(px2->plo, 54, void (*)(void *, struct LO *)), px->plo);
            pv = pl->pv;
            func_001A7E10(p, pv);
            { void *pvNew = PxpMarkOxaContacts__FP3OXAT0P2SO(p, px, px2); pl->pv = pvNew; pl->pother->pv = pvNew; }
            if (pv || pl->pv) {
                if (!VCALL(px->plo, 62, int (*)(void *))))
                    WakeAlo__FP3ALO(px->plo);
                if (!VCALL(px2->plo, 62, int (*)(void *))))
                    WakeAlo__FP3ALO(px2->plo);
            }
        }
    }
    for (px = p->pxFirst; px; px = p->pxFirst) {
        px->grf &= ~0x10L;
        VCALL(px->plo, 54, void (*)(void *, struct LO *)), 0);
        func_001A7E10(p, px->pv68);
        px->pv68 = 0;
        VCALL(px->plo, 59, void (*)(void *)));
        px->grf &= ~2L;
        RemoveDlEntry__FP2DLPv(&p->pxFirst, px);
    }
    for (i = 0; i < c; i++) {
        px = apx[i];
        px->grf &= ~8L;
        VCALL(px->plo, 58, void (*)(void *)));
    }
    _$_10STACKSCOPE(&ctx, 2);
}
