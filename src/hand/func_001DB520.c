typedef struct { short d; short pad; void *pfn; } VTE;
typedef struct { char pad0[0xC]; VTE *vt; } SUB;
typedef struct {
    int key;
    int a;
    int b;
    int c;
    int cur;
    float x14;
    float x18;
    int flags;
} E;
typedef struct OBJ {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x20 - 0x10];
    int x20;
    SUB *x24;
    char pad28[0x40 - 0x28];
    int x40;
    float x44;
    int x48;
    int n;
    E *ae;
} OBJ;
extern struct CLOCK { float a[16]; } g_clock;
extern char g_sw[];
extern E D_002C2DE8[], D_002C3028[], D_002C3148[];
extern float D_002A79CC;
void SetClockFactor__FP5CLOCKif(struct CLOCK *, float, int);
void PauseGame__FP9GAMEPAUSEi(void *, int);
void ResumeGame__FP9GAMEPAUSEi(void *, int);
void SelectGadget__FPvi(OBJ *, int);
void SetShopMsg__FP4SHOPii(OBJ *, int, int);
void UpdateGadgetFlags__FPv(OBJ *);
SUB *PloFindSwNearest__FP2LO3OIDii(void *, int, int, int);
void SetGadgetMenu__FPvi(OBJ *p, int s);
#define VCALL(o, n) ((void (*)(void *))(o)->vt[n].pfn)((char *)(o) + (o)->vt[n].d)
// name: SafeHouse port (SetGadgetMenu)
void SetGadgetMenu__FPvi(OBJ *p, int s)
{
    if (s == p->x40)
        return;
    if (p->x40 == -1) {
        SetClockFactor__FP5CLOCKif(&g_clock, 0.0f, 0);
        PauseGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(p, 10);
    }
    SelectGadget__FPvi(p, -1);
    p->x40 = s;
    p->x44 = g_clock.a[15];
    switch (s) {
    case -1: {
        int i;
        if (p->x24)
            VCALL(p->x24, 50);
        for (i = 0; i < p->n; i++)
            p->ae[i].cur = -1;
        p->n = 0;
        p->ae = 0;
        SetClockFactor__FP5CLOCKif(&g_clock, 1.0f, 0);
        ResumeGame__FP9GAMEPAUSEi(g_sw, 0);
        VCALL(p, 11);
        SetShopMsg__FP4SHOPii(p, -1, -1);
        p->x24 = 0;
        p->x20 = -1;
        break;
    }
    case 0:
        p->x20 = 0x375;
        p->n = 0x12;
        p->ae = D_002C2DE8;
        break;
    case 1:
        p->x20 = 0x376;
        p->n = 9;
        p->ae = D_002C3028;
        break;
    case 2:
        p->x20 = 0x377;
        p->n = 8;
        p->ae = D_002C3148;
        break;
    }
    if (p->x40 != -1) {
        SUB *e;
        UpdateGadgetFlags__FPv(p);
        e = PloFindSwNearest__FP2LO3OIDii(g_sw, 5, p->x20, 0);
        p->x24 = e;
        if (!e) {
            SetGadgetMenu__FPvi(p, -1);
        } else {
            float best;
            int key;
            int i;
            ((void (*)(void *, int))e->vt[49].pfn)((char *)e + e->vt[49].d, 0x318);
            best = D_002A79CC;
            key = -1;
            for (i = 0; i < p->n; i++) {
                E *pe = &p->ae[i];
                if (pe->flags & 4) {
                    float f = pe->x14 + pe->x18;
                    if (f < best) {
                        key = pe->key;
                        best = f;
                    }
                }
            }
            SelectGadget__FPvi(p, key);
        }
    }
}
