struct BS { int n0; int n4; int n8; };
struct X { char pad[0xC]; int c; };
struct T1 { char pad[0x18]; long l18; };
struct T2 { char pad[0x20]; long l20; };
struct E1 { int n0; unsigned char b4; char pad5[5]; unsigned short hA; int nC; int n10; char pad14[4]; long l18; };
struct E2 { int n0; unsigned char b4; char pad5[7]; unsigned char bC; char padD; unsigned short hE; char pad10[4]; int n14; int n18; char pad1C[4]; long l20; };
extern int D_003DCFF8;
extern struct E1 *D_003DCFFC;
extern int D_003DCFF0;
extern struct E2 *D_003DCFF4;
struct T1 *func_001ED5D0(int);
struct T2 *func_001ED4E0(int);
int func_00170548(struct BS *, int);
void func_001EC9D0(struct E1 *, int);
void BuildClutGifs(struct E1 *, int, struct X *) asm("BuildClutGifs__FP4CLUTiP4GIFS");
void BuildBmpTex0(struct E2 *, int) asm("BuildBmpTex0__FP3BMPi");
void func_001ECBF0(struct E2 *, int, struct X *);
void AddDmaRefs(struct X *, int, int) asm("AddDmaRefs__4DMASiP2QW");
void func_001ED560(struct E1 *);
void func_001ED470(struct E2 *);
int func_001ECC28(int k, struct BS *pbs, struct X *px)
{
    int c0 = 0;
    int i, j;
    if (px)
        c0 = px->c;
    for (i = 0; i < D_003DCFF8; i++) {
        struct E1 *pe = &D_003DCFFC[i];
        struct T1 *pt;
        int v;
        if (k != pe->b4)
            continue;
        pt = func_001ED5D0(pe->n0);
        if (pt) {
            pe->l18 = pt->l18;
            continue;
        }
        v = func_00170548(pbs, pe->hA);
        func_001EC9D0(pe, v);
        if (px && pbs->n4 <= pbs->n8) {
            BuildClutGifs(pe, v, px);
            AddDmaRefs(px, pe->n10, pe->nC);
        }
        func_001ED560(pe);
    }
    for (j = 0; j < D_003DCFF0; j++) {
        struct E2 *pe = &D_003DCFF4[j];
        struct T2 *pt;
        int v;
        if (k != pe->b4)
            continue;
        pt = func_001ED4E0(pe->n0);
        if (pt) {
            pe->l20 = pt->l20;
            continue;
        }
        if (!pe->bC) {
            int r = pbs->n4 & 0x1F;
            if (r)
                func_00170548(pbs, 32 - r);
        }
        v = func_00170548(pbs, pe->hE);
        BuildBmpTex0(pe, v);
        if (px && pbs->n4 <= pbs->n8) {
            func_001ECBF0(pe, v, px);
            AddDmaRefs(px, pe->n18, pe->n14);
        }
        func_001ED470(pe);
    }
    if (!px)
        return 0;
    return px->c != c0;
}
