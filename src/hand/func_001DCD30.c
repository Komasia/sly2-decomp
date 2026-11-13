typedef struct VT { struct { short d; short pad; void (*pfn)(void *); } a[32]; } VT;
typedef struct { char pad[0xC]; VT *vt; char pad10[0x58 - 0x10]; int x58; } W;
typedef struct {
    char pad[0x10];
    void *x10;
    char pad14[0x24 - 0x14];
    W *pw;
    char pad28[0x40 - 0x28];
    int x40;
    char pad44[4];
    int c;
    char pad4c[0x114 - 0x4C];
    int x114;
} OBJ;
void func_001DA808(OBJ *);
int func_002127C8(void);
void SetState__FP8SCREENRTi(W *, int);
void SetTimerTimers(W *, int) asm("SetTimerTimers__FP5TIMER6TIMERS");
int func_00187D80(void *, int);
void SetJobHelpPage__FPvi(OBJ *, int);
void UpdateShopStick__FP4SHOP(OBJ *);
void UpdateJobHelpLook__FPv(OBJ *);
// name: SafeHouse port (UpdateJobHelp)
void UpdateJobHelp__FP2SW(OBJ *p)
{
    func_001DA808(p);
    if (p->x40 == -1)
        return;
    if (p->x10 == 0)
        return;
    if (p->pw->x58 == 0) {
        if (!func_002127C8())
            return;
        SetState__FP8SCREENRTi(p->pw, 1);
        SetTimerTimers(p->pw, 2);
        p->pw->vt->a[16].pfn((char *)p->pw + p->pw->vt->a[16].d);
    }
    if (func_00187D80(p->x10, 0x800)) {
        SetJobHelpPage__FPvi(p, -1);
        return;
    }
    switch (p->x40) {
    case 0:
        if (func_00187D80(p->x10, 0x10)) {
            SetJobHelpPage__FPvi(p, -1);
            return;
        }
        if (p->c && func_00187D80(p->x10, 0xF0)) {
            SetJobHelpPage__FPvi(p, 1);
            return;
        }
        break;
    case 1:
        if (!p->x114 && func_00187D80(p->x10, 0x10)) {
            SetJobHelpPage__FPvi(p, -1);
            return;
        }
        if (func_00187D80(p->x10, 0xF0)) {
            SetJobHelpPage__FPvi(p, 0);
            return;
        }
        break;
    }
    UpdateShopStick__FP4SHOP(p);
    UpdateJobHelpLook__FPv(p);
}
