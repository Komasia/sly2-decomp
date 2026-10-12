struct DL { void *a, *b; int ib; };
struct S { char pad[0x58]; int n58; struct DL dl; };
void func_001A5270(struct S *p);
void func_0011A1F8(struct DL *pdl, int ib);
void func_001DFAD8(struct S *p) {
    func_001A5270(p);
    p->n58 = -1;
    func_0011A1F8(&p->dl, 0xE4);
}
