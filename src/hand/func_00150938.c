typedef struct CLOCK { float t; float dt; } CLOCK;
extern CLOCK g_clock;
extern float D_003E1BE0;
struct G { char pad[0x24]; float g24; char pad2[0x60 - 0x28]; char mat[0x4A4 - 0x60]; int c4A4; };
extern struct G g_cm;
struct A { char pad[0xA4]; float gA4; float gA8; int nAC; int nB0; float gB4; float gB8; float gBC; void *pC0; void *pC4; };
void Activate__5CPLCYP2LOPv(struct A *a, int n);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void func_00258040(void **pp, void *p);
void Pause__4CSnd(void *p);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(void *pmat, float *pa, float *pb);
void SetCmNearClip__FP2CMf(struct G *pg, float g);
void Snap__6CPFREE(struct A *a);
// name: SafeHouse port (CPFREE::Activate)
void Activate__6CPFREEP2LOPv(struct A *a, int n)
{
    void *p;
    struct G *pg;
    Activate__5CPLCYP2LOPv(a, n);
    p = PsndNewPlain__Fi(0x26);
    SetSource__4CSndPv(p, 0);
    func_00258040(&a->pC0, p);
    p = PsndNewPlain__Fi(0x25);
    SetSource__4CSndPv(p, 0);
    func_00258040(&a->pC4, p);
    Pause__4CSnd(a->pC0);
    __asm__ __volatile__("" ::: "$6"); /* a2 is dead here: delays the a2 setup like the original */
    pg = &g_cm;
    DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(pg->mat, &a->gA4, &a->gA8);
    a->gA8 = 0;
    a->nAC = 0;
    a->nB0 = 0;
    a->gB8 = pg->g24 / a->gB4;
    a->gBC = pg->g24;
    SetCmNearClip__FP2CMf(pg, 49.0f);
    Snap__6CPFREE(a);
    pg->c4A4++;
    D_003E1BE0 = g_clock.t;
}
