struct X { char pad[0x98]; short f98; char pad2[0xe]; float fa8; };
struct N { int f0; int f4; struct X *px; char pad[0x1c]; struct N *pnext; };
struct S { char pad[0x34]; struct N *pfirst; };
int FFirst__4CTRL(struct N *);
void SetXfMode__FP3ALOP2XFi(int, struct X *, int);
void func_00131A90(struct S *p, float g) {
    struct N *pn;
    for (pn = p->pfirst; pn; pn = pn->pnext) {
        if (FFirst__4CTRL(pn) && pn->px->f98 == 7) {
            SetXfMode__FP3ALOP2XFi(pn->f4, pn->px, 9);
            pn->px->fa8 = g;
        }
    }
}
