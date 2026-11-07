typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct SO { char pad[0xC]; struct VTE *vt; char pad1[0x240 - 0x10]; qword pos; };
struct X {
    char pad[0x10]; struct SO *pso; int x14; void *x18; char pad1[0x30 - 0x1C]; int state; float t34;
    char pad2[0x40 - 0x38]; void *x40; float t44; float t48; int x4C; char pad3[0x54 - 0x50]; int x54;
};
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern qword D_002A2DD0;
void Update__5AIJOB(struct X *p);
int func_001EF0A8(struct X *p);
int func_00174FB8(void *p);
int FArrived__9JOBFOLLOW(void *p);
int func_00175748(void *p);
int PactionSelect__FP5GUARDP2LOP9TARGETREC(struct SO *p, int n, int z);
qword PosOfLo__FP2LO(void *p);
void SetB5State__5JOBB5i(struct X *p, int k);
void *PloEnd__5JOBB5(struct X *p);

static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
// name: SafeHouse port (JOBB5::Update)
void Update__5JOBB5(struct X *p)
{
    Update__5AIJOB(p);
    while (!func_001EF0A8(p)) {
        int s = p->state;
        switch (s) {
        case 0:
            if (func_00174FB8(p->x18)) {
                struct SO *pso;
                qword d = Sub(PosOfLo__FP2LO(p->x40), p->pso->pos);
                pso = p->pso;
                ((void (*)(void *, qword))pso->vt[29].pfn)((char *)pso + pso->vt[29].d, d);
                pso = p->pso;
                ((void (*)(void *, qword))pso->vt[35].pfn)((char *)pso + pso->vt[35].d, D_002A2DD0);
                pso = p->pso;
                ((void (*)(void *, qword))pso->vt[36].pfn)((char *)pso + pso->vt[36].d, D_002A2DD0);
                p->t48 = g_clock.t;
                SetB5State__5JOBB5i(p, 1);
            }
            break;
        case 2:
            if (FArrived__9JOBFOLLOW(p->x18))
                SetB5State__5JOBB5i(p, 1);
            break;
        case 1:
            if (2.5f < g_clock.t - p->t48 && 0.1f < g_clock.t - p->t34) {
                if ((p->x54 = PactionSelect__FP5GUARDP2LOP9TARGETREC(p->pso, p->x4C, 0)) != 0)
                    SetB5State__5JOBB5i(p, 3);
            }
            break;
        case 3:
            p->t44 = g_clock.t;
            if (func_00175748(p->x18)) {
                int k = 1;
                void *n = PloEnd__5JOBB5(p);
                if (n != p->x40) {
                    p->x40 = n;
                    k = 2;
                }
                SetB5State__5JOBB5i(p, k);
            }
            break;
        }
        if (s == p->state) return;
    }
}
