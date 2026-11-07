struct M { int n0; int n4; int n8; };
struct T { char pad[0xF3C]; int nF3C; };
struct P { char pad[8]; int n8; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x2C]; struct P *p40; char pad3[0xC]; int n50; };
int PasegaOfKinde__FP5KINDE(void *p);
int Message__7JOBMOVEiPv(struct S *p, int msg, struct M *pm);
void ReleaseK2Ballistic__FP6K2PLAY(int n);
// name: SafeHouse port (JOBSTRIKE::Message)
int Message__9JOBSTRIKEiPv(struct S *p, int msg, struct M *pm) {
    if (msg == 9 && p->p40 && PasegaOfKinde__FP5KINDE(p->p40) == pm->n0) {
        switch (pm->n8) {
        case 0x2D: p->pt->nF3C = 1; return 1;
        case 0x2E: p->pt->nF3C = 0; return 1;
        case 0x30: p->n50 = 0; ReleaseK2Ballistic__FP6K2PLAY(p->p40->n8); return 1;
        }
    }
    return Message__7JOBMOVEiPv(p, msg, pm);
}
