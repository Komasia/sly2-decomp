typedef int qword __attribute__((mode(TI)));
struct V3 { float x, y, z; };
struct Y14 { char pad[0x78]; float f78; };
struct Y { char pad[0x14]; struct Y14 *p14; };
struct X { char pad[0x40]; void *p40; };
struct Z { char pad[0x30]; int k30; char pad2[0x40 - 0x34]; int n40; float f44; };
struct S { char pad[0x190]; struct V3 v190; char pad2[0xFBC - 0x19C]; int k; float t; void *pFC4; };
extern struct { float t; float dt; } g_clock;
extern qword D_002A2DE0;
extern qword D_002C3D30;
extern float D_002A8698;
extern char g_sw[];
int FGuardModeAllowed__FP5GUARDi(struct S *p, int k);
void SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(void *p, qword q);
void RemoveTargetClass__FPvi(struct S *p, int n);
void func_00206E50(struct S *p);
void func_00208700(struct S *p, int n);
void func_00206DB0(struct S *p);
void *func_00205458(struct S *p, int n);
struct Y *PasegaOfKinde__FP5KINDE(void *p);
void SetAsegaAsegSpeed__FP5ASEGAf(struct Y *y, float f);
int PloPlayerPo__FP2SW(void *p);
void NextReaction__8JOBREACT(struct Z *z);

// name: SafeHouse port (SetGuardMode)
void SetGuardMode__FP5GUARDi(struct S *p, int k)
{
    int old;
    if (k == p->k)
        return;
    if (!FGuardModeAllowed__FP5GUARDi(p, k))
        return;
    old = p->k;
    p->k = k;
    p->t = g_clock.t;
    switch (old) {
    case 8:
    case 0xD:
        if (p->pFC4)
            SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(p->pFC4, D_002A2DE0);
        break;
    case 0x22:
    case 0x25:
        RemoveTargetClass__FPvi(p, 0x38);
        func_00206E50(p);
        break;
    case 0xE: {
        struct X *x = func_00205458(p, 0x9D);
        if (x) {
            struct Y *y = PasegaOfKinde__FP5KINDE(x->p40);
            if (y)
                SetAsegaAsegSpeed__FP5ASEGAf(y, y->p14->f78);
        }
        break;
    }
    case 0x15: {
        struct Z *z = func_00205458(p, 0x9C);
        if (z && z->k30 == 0x12 && z->n40 == PloPlayerPo__FP2SW(g_sw) && z->f44 == D_002A8698)
            NextReaction__8JOBREACT(z);
        break;
    }
    }
    switch (k) {
    case 8:
    case 0xD:
        if (p->pFC4)
            SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(p->pFC4, D_002C3D30);
        break;
    case 0x22:
    case 0x25:
        func_00208700(p, 0x38);
        func_00206DB0(p);
        break;
    case 0xE: {
        struct X *x = func_00205458(p, 0x9D);
        if (x) {
            struct Y *y = PasegaOfKinde__FP5KINDE(x->p40);
            if (y)
                SetAsegaAsegSpeed__FP5ASEGAf(y, 0.0f);
        }
        {
            struct V3 *pv = &p->v190;
            pv->z = 0;
            pv->y = 0;
            pv->x = 0;
        }
        break;
    }
    case 0x15: {
        struct Z *z = func_00205458(p, 0x9C);
        if (z) {
            switch (z->k30) {
            case 1: case 2: case 3: case 4:
            case 0xC: case 0x10: case 0x11: case 0x12:
                NextReaction__8JOBREACT(z);
                break;
            }
        }
        break;
    }
    }
}
