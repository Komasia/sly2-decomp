typedef struct { char pad0[0xC]; void *vt; } SUB;
typedef struct Q {
    char pad0[0xDFC];
    int xDFC;
    int *xE00;
    char pad[0x10C8 - 0xE04];
    int x10C8;
    char pad2[0x10EC - 0x10CC];
    int x10EC;
    char pad3[0x1300 - 0x10F0];
    int x1300;
} Q;
typedef struct OBJ {
    char pad0[0x20];
    float x20;
    float x24;
    float x28;
    float x2C;
    int x30;
    Q *x34;
    SUB *x38;
    int x3C;
    int x40;
    int x44;
    int x48;
    int x4C;
} OBJ;
extern struct G g_sw;
extern struct { float t; float dt; } g_clock;
extern char D_002C3248[];
Q *PloPlayerPo__FP2SW(struct G *);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
void SetGaugeState__FP5GAUGEi(OBJ *, int);
int func_001441A0(Q *);
int func_0011D4D0(float, float, float);
float GSmooth__FfffP3SMPPf(void *, int, float, float, float);
int FSpriteAnimPlaying__FP2LOi(SUB *, int);
void func_00212E40(SUB *, int, float);
// name: SafeHouse port (UpdateGauge)
void UpdateGauge__FP5GAUGE(OBJ *p)
{
    Q *old;
    Q *q;
    if (!p->x38)
        return;
    old = p->x34;
    p->x34 = 0;
    q = PloPlayerPo__FP2SW(&g_sw);
    if (q && FIsBasicDerivedFrom__FP5BASIC3CID(q, 0x34))
        p->x34 = q;
    if (!p->x34) {
        p->x20 = p->x24 = 0;
        p->x28 = p->x2C = 0;
        if (old)
            SetGaugeState__FP5GAUGEi(p, 0);
        return;
    }
    if (old != p->x34) {
        if (!old)
            SetGaugeState__FP5GAUGEi(p, 3);
        else
            SetGaugeState__FP5GAUGEi(p, 5);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x34, 0x35)) {
            p->x3C = 0x33D; p->x40 = 0x33E; p->x44 = 0x33F; p->x48 = 0x340; p->x4C = 0x341;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x34, 0x37)) {
            p->x3C = 0x347; p->x40 = 0x348; p->x44 = 0x349; p->x48 = 0x34A; p->x4C = 0x34B;
        } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x34, 0x36)) {
            p->x3C = 0x342; p->x40 = 0x343; p->x44 = 0x344; p->x48 = 0x345; p->x4C = 0x346;
        }
        p->x20 = p->x24 = (float)*p->x34->xE00 / (float)p->x34->xDFC;
        p->x28 = p->x2C = (float)func_001441A0(p->x34) / (float)p->x34->x1300;
    }
    switch (p->x30) {
    case 1:
    case 6:
    case 7:
        p->x24 = (float)*p->x34->xE00 / (float)p->x34->xDFC;
        p->x2C = (float)func_001441A0(p->x34) / (float)p->x34->x1300;
        if (*p->x34->xE00 <= 0) {
            SetGaugeState__FP5GAUGEi(p, 0);
        } else if (p->x20 > p->x24) {
            SetGaugeState__FP5GAUGEi(p, 2);
        } else if (p->x20 < p->x24) {
            SetGaugeState__FP5GAUGEi(p, 3);
        } else if (!func_0011D4D0(p->x28, p->x2C, 0.0001f)) {
            SetGaugeState__FP5GAUGEi(p, 4);
        } else if (p->x34->x10EC == 4) {
            SetGaugeState__FP5GAUGEi(p, 7);
        } else if (p->x34->x10C8 != -1) {
            SetGaugeState__FP5GAUGEi(p, 6);
        } else {
            SetGaugeState__FP5GAUGEi(p, 1);
        }
        break;
    case 2:
        if (!FSpriteAnimPlaying__FP2LOi(p->x38, p->x40))
            SetGaugeState__FP5GAUGEi(p, 3);
        break;
    case 5:
        if (!FSpriteAnimPlaying__FP2LOi(p->x38, p->x44))
            SetGaugeState__FP5GAUGEi(p, 1);
        break;
    case 0:
        p->x24 = (float)*p->x34->xE00 / (float)p->x34->xDFC;
        p->x2C = (float)func_001441A0(p->x34) / (float)p->x34->x1300;
        if (p->x20 < p->x24) {
            p->x20 = p->x24;
            func_00212E40(p->x38, 0x34F, 1.0f - p->x20);
            p->x28 = p->x2C;
            func_00212E40(p->x38, 0x350, 1.0f - p->x28);
            SetGaugeState__FP5GAUGEi(p, 1);
        }
        break;
    case 3:
        p->x24 = (float)*p->x34->xE00 / (float)p->x34->xDFC;
        if (p->x20 < p->x24)
            p->x20 = p->x24;
        else
            p->x20 = GSmooth__FfffP3SMPPf(D_002C3248, 0, p->x20, p->x24, g_clock.dt);
        func_00212E40(p->x38, 0x34F, 1.0f - p->x20);
        if (func_0011D4D0(p->x20, p->x24, 0.0001f))
            SetGaugeState__FP5GAUGEi(p, 1);
        break;
    case 4:
        p->x2C = (float)func_001441A0(p->x34) / (float)p->x34->x1300;
        if (p->x28 < p->x2C)
            p->x28 = p->x2C;
        else
            p->x28 = GSmooth__FfffP3SMPPf(D_002C3248, 0, p->x28, p->x2C, g_clock.dt);
        func_00212E40(p->x38, 0x350, 1.0f - p->x28);
        if (func_0011D4D0(p->x28, p->x2C, 0.0001f))
            SetGaugeState__FP5GAUGEi(p, 1);
        break;
    }
}
