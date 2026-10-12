struct K { int k; };
struct R { struct K *pk; int n; float g; };
struct U { char pad[0x38]; float g38; };
struct T { char pad[0xF80]; int nF80; };
struct S { char pad[0x10]; struct T *pt; int pad1; struct U *p18; char pad2[0x18]; int n34; struct K *p38; };
void *func_002333B4(void *p, int c, int n);
void func_00171C18(struct S *p, struct R *r) {
    switch (p->pt->nF80) {
    case -1:
        r->pk = p->p38;
        r->n = p->n34;
        if (r->pk && r->pk->k == 6) r->g = p->p18->g38;
        break;
    case 0: case 1:
        func_002333B4(r, 0, sizeof(*r));
        break;
    }
}
