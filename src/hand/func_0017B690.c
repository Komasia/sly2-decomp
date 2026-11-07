struct M { int n0; int n4; int n8; };
struct U { char pad[0x40]; void *p40; };
struct T { char pad[0xF60]; int nF60; };
struct S { char pad[0x10]; struct T *pt; int pad2; struct U *p18; char pad3[0x14]; int n30; };
int PasegaOfKinde__FP5KINDE(void *p);
int Message__5AIJOBiPv(struct S *p, int msg, struct M *pm);
// name: SafeHouse port (JOBSHOOT::Message)
int Message__8JOBSHOOTiPv(struct S *p, int msg, struct M *pm) {
    if (msg == 9 && !p->n30 && p->p18->p40 && PasegaOfKinde__FP5KINDE(p->p18->p40) == pm->n0) {
        switch (pm->n8) {
        case 0x31: p->pt->nF60 = 1; return 1;
        case 0x32: p->pt->nF60 = 0; return 1;
        }
    }
    return Message__5AIJOBiPv(p, msg, pm);
}
