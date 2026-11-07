typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern "C" struct CLOCK g_clock;
extern "C" qword D_002A2DD0;
extern "C" char g_game[];
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct O { char pad[0xC]; struct VTE *vt; int n10; };
struct N { char pad[0xA0]; int nA0; };
struct E { void *p0; int pad[5]; };
struct Q { int a[4]; };
struct S {
    char pad[0xC]; struct VTE *vt; char pad2[0x44]; struct N *p54; struct N *p58; struct N *p5C;
    char pad3[0x1C0 - 0x60]; int n1C0; float f1C4; struct Q a1C8[6]; char padq[8]; int n230;
    char pad4[0x248 - 0x234]; struct E a248[3]; int pade; struct O *p294; int n298; int n29C; struct O *p2A0; void *p2A4; int n2A8;
};
extern "C" {
void func_00213B00(struct O *o, int n);
void UpdateHackHud(struct S *p) asm("UpdateHackHud__FP2LO");
void *PsndNewPlain(int n) asm("PsndNewPlain__Fi");
void SetSource(void *p, int n) asm("SetSource__4CSndPv");
void func_00258040(void **pp, void *q);
void Pause(void *p) asm("Pause__4CSnd");
void DeleteCtrl(int *p) asm("DeleteCtrl__FPP4CTRL");
void SetXfMode(struct S *p, struct N *n, int k) asm("SetXfMode__FP3ALOP2XFi");
void func_001A58D0(struct S *p, int a, int b);
void SetAloCnstrLin(struct S *p, int n) asm("SetAloCnstrLin__FP3ALOi");
void SetAloCnstrAng(struct S *p, int n) asm("SetAloCnstrAng__FP3ALOi");
void SetAloSensors(struct S *p, int n) asm("SetAloSensors__FP3ALOi");
void func_001F0660(void *p, int n);
void Stop(void *p, float f) asm("Stop__4CSndf");
struct M4 func_0022FF40(int a, int b, struct M4 *pm);
int PctrlNewPos(struct S *p, struct N *n, int a, int b, int c, qword v) asm("PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR");
qword func_0011BFF0(struct M4 *pm);
void BroadcastTaskEvent(void *a, int n, struct S *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
void PlayHackSeg(struct S *p, struct Q *q) asm("PlayHackSeg__FP2LOP6HACKSO");
void SetShipState(struct S *p, int n) asm("SetShipState__FP2LOi");
}
// name: SafeHouse port (SetShipState)
void SetShipState(struct S *p, int n) {
    int old = p->n1C0;
    if (n == old) return;
    switch (old) {
    case -1:
        {
            struct O *q = p->p2A0;
            if (q) {
                { struct VTE *e = &q->vt[0x31]; ((void (*)(void *, int))e->pfn)((char *)q + e->d, -1); }
                func_00213B00(p->p2A0, 0x34F);
                UpdateHackHud(p);
                if (p->n2A8 != old) {
                    void *r = PsndNewPlain(p->n2A8);
                    SetSource(r, 0);
                    func_00258040(&p->p2A4, r);
                    Pause(p->p2A4);
                }
            }
        }
        break;
    case 3:
        DeleteCtrl(&p->n298);
        DeleteCtrl(&p->n29C);
        SetXfMode(p, p->p58, 2);
        SetXfMode(p, p->p5C, 2);
        func_001A58D0(p, 0, 0xF);
        SetAloCnstrLin(p, 5);
        SetAloCnstrAng(p, 4);
        SetAloSensors(p, 0);
        p->p294 = 0;
        break;
    case 1:
        {
            int i;
            for (i = 0; i < p->n230; i++) {
                if (p->a248[i].p0) func_001F0660(p->a248[i].p0, 0x66);
            }
        }
        break;
    }
    p->n1C0 = n;
    p->f1C4 = g_clock.t;
    switch (n) {
    case -1:
        {
            struct O *q = p->p2A0;
            if (q) { struct VTE *e = &q->vt[0x32]; ((void (*)(void *))e->pfn)((char *)q + e->d); }
            void **pp = &p->p2A4;
            if (*pp) {
                Stop(*pp, 0.0f);
                func_00258040(pp, 0);
            }
        }
        break;
    case 3:
        {
            struct M4 m;
            int r;

            { struct O *q = p->p294; struct VTE *e = &q->vt[0x20]; r = ((int (*)(void *, struct M4 *))e->pfn)((char *)q + e->d, &m); }
            m = func_0022FF40(p->p54->nA0, p->p58->nA0, &m);
            { struct VTE *e = &p->vt[0xA]; ((void (*)(void *, int, int, int))e->pfn)((char *)p + e->d, p->p294->n10, r, 3); }
            { struct VTE *e = &p->vt[0x23]; ((void (*)(void *, qword))e->pfn)((char *)p + e->d, D_002A2DD0); }
            { struct VTE *e = &p->vt[0x24]; ((void (*)(void *, qword))e->pfn)((char *)p + e->d, D_002A2DD0); }
            p->n298 = PctrlNewPos(p, p->p58, 1, 7, 2, m.r[3]);
            p->n29C = PctrlNewPos(p, p->p5C, 1, 7, 2, func_0011BFF0(&m));
            SetAloCnstrLin(p, 1);
            SetAloCnstrAng(p, 1);
            SetAloSensors(p, 1);
        }
        break;
    case 4:
        BroadcastTaskEvent(g_game, 0x10, p);
        break;
    }
    PlayHackSeg(p, n == -1 ? 0 : &p->a1C8[n]);
}
