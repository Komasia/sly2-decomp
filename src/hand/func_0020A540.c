struct O { char pad[0x30]; int n30; };
struct L { int k; int rest[27]; };
struct S { char pad[0x26C]; char x26C[0x2DC - 0x26C]; int a2DC[3]; int n2E8; };
void *s1_memset(void *p, int c, int n);
struct O *PjobFind__FP5GUARDPv(void *p, int n);
void React__8JOBREACTP5AIMSG(struct O *po, struct L *pl);
// name: SafeHouse port (SetGuardPatrol)
void SetGuardPatrol__FP5GUARDi(struct S *p, int n)
{
    if (p->n2E8 != n) {
        struct O *po;
        p->n2E8 = n;
        s1_memset(p->a2DC, 0, 0xC);
        po = PjobFind__FP5GUARDPv(p->x26C, 0x9C);
        if (po) {
            int k = po->n30;
            if (k == 1) {
                struct L l;
                s1_memset(&l, 0, sizeof(l));
                l.k = -1;
                React__8JOBREACTP5AIMSG(po, &l);
                s1_memset(p->a2DC, 0, 0xC);
                l.k = k;
                React__8JOBREACTP5AIMSG(po, &l);
            }
        }
    }
}
