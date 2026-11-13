typedef struct { float a, b; } F2;
struct G { char pad[0x24]; float x24; char pad2[0x60 - 0x28]; int x60; };
extern struct G g_cm;
extern struct { float t; float dt; } g_clock;
extern float D_003E1BE0;
extern F2 D_002BD950, D_002BD958, D_002BD960, D_002BD968, D_002BD970;
struct X {
    int x0; char pad[0xC]; float x10; float x14; int x18; int x1C; int x20; int x24; float x28; float x2C; float x30;
    int x34; int x38; F2 x3C; F2 x44; float x4C; float x50; int x54;
};
void Activate__5CPLCYP2LOPv(struct X *p);
void *PsndNewPlain__Fi(int);
void SetSource__4CSndPv(void *, int);
void func_00258040(int *, void *);
void Pause__4CSnd(int);
void DecomposeRotateMatrixPanTilt(void *, float *, float *) asm("DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1");
int FIsBasicDerivedFrom__FP5BASIC3CID(int, int);
void *MatJtLo__FP2LO(int);
float GLimitLm(F2 *, float) asm("GLimitLm__FP2LMf");
void SetCmNearClip__FP2CMf(struct G *, float);

// name: SafeHouse port (CPRECON::Activate)
void Activate__7CPRECONP2LOPv(struct X *p)
{
    struct G *pg;
    void *pv;
    float g;
    Activate__5CPLCYP2LOPv(p);
    pv = PsndNewPlain__Fi(0x26);
    SetSource__4CSndPv(pv, 0);
    func_00258040(&p->x34, pv);
    {
        void *pv2 = PsndNewPlain__Fi(0x25);
        SetSource__4CSndPv(pv2, 0);
        func_00258040(&p->x38, pv2);
    }
    Pause__4CSnd(p->x34);
    pg = &g_cm;
    DecomposeRotateMatrixPanTilt(&pg->x60, &p->x10, &p->x14);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x0, 0x34)) {
        p->x3C = D_002BD950;
        p->x44 = D_002BD958;
    } else {
        p->x3C = D_002BD968;
        p->x44 = D_002BD970;
        p->x4C = p->x10;
        p->x50 = p->x14;
        DecomposeRotateMatrixPanTilt(MatJtLo__FP2LO(p->x0), &p->x10, &p->x14);
        g = GLimitLm(&D_002BD960, p->x14);
        p->x14 = g;
        p->x3C.a += p->x10;
        p->x3C.b += p->x10;
        p->x44.a += g;
        p->x44.b += g;
        p->x44.a = GLimitLm(&D_002BD960, p->x14);
        p->x44.b = GLimitLm(&D_002BD960, p->x14);
    }
    p->x18 = 0;
    p->x1C = 0;
    p->x20 = 0;
    p->x24 = 0;
    p->x2C = g_cm.x24 / p->x28;
    p->x30 = g_cm.x24;
    SetCmNearClip__FP2CMf(&g_cm, 49.0f);
    p->x54++;
    D_003E1BE0 = g_clock.t;
}
