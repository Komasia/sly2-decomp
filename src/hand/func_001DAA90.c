typedef struct { char pad[0x1C]; int fl; } R;
typedef struct {
    char pad[0x10];
    void *x10;
    char pad14[0x24 - 0x14];
    void *x24;
    char pad28[0x30 - 0x28];
    int x30;
    char pad34[0x40 - 0x34];
    int x40;
    char pad44[4];
    int x48;
} OBJ;
extern struct G g_sw;
extern int D_002C3258[];
void func_001DA808(OBJ *);
int func_00187D80(void *, int);
void *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void SetGadgetMenu__FPvi(OBJ *, int);
void UpdateShopStick__FP4SHOP(OBJ *);
R *func_001DAE20(OBJ *, int);
void SetShopMsg__FP4SHOPii(OBJ *, int, int);
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void SetActorAbilitySlot__FP5ACTORii(void *, int, int);
// name: SafeHouse port (UpdateGadgetMenu)
void UpdateGadgetMenu__FP2SW(OBJ *p)
{
    void *pv;
    R *r;
    int i;
    func_001DA808(p);
    if (p->x24 == 0)
        return;
    if (p->x40 == -1)
        return;
    if (p->x10 == 0)
        return;
    if (p->x30 && func_00187D80(p->x10, 0x10)) {
        SetGadgetMenu__FPvi(p, -1);
        return;
    }
    pv = PloPlayerPo__FP2SW(&g_sw);
    if (pv == 0 || !FIsBasicDerivedFrom__FP5BASIC3CID(pv, 0x34)) {
        SetGadgetMenu__FPvi(p, -1);
        return;
    }
    UpdateShopStick__FP4SHOP(p);
    if (func_00187D80(p->x10, 0x7E8)) {
        r = func_001DAE20(p, p->x48);
        if (r == 0 || !(r->fl & 1))
            SetShopMsg__FP4SHOPii(p, 1, 0xE2);
        else
            SetShopMsg__FP4SHOPii(p, 1, 0x31);
    }
    for (i = 0; i < 3; i++) {
        if (!func_00187D80(p->x10, D_002C3258[i]))
            continue;
        r = func_001DAE20(p, p->x48);
        if (r == 0 || !(r->fl & 4)) {
            SetShopMsg__FP4SHOPii(p, 1, 0x32);
        } else if (!(r->fl & 1)) {
            SetShopMsg__FP4SHOPii(p, 1, 0x33);
        } else {
            SetSource__4CSndPv(PsndNewPlain__Fi(0x34), 0);
            SetActorAbilitySlot__FP5ACTORii(pv, i, p->x48);
        }
    }
}
