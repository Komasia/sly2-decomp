typedef unsigned long ulong;
typedef int qword __attribute__((mode(TI)));
struct BS { int n0; int n4; int n8; };
struct DMAS { int pad[3]; qword *pqw; int pad2[8]; };
struct X { int pad[12]; };
struct M { int pad[4]; };
struct E1 { int n0; unsigned char b4; char pad5[5]; unsigned short hA; int nC; int n10; char pad14[0xC]; };
struct E2 { int n0; unsigned char b4; char pad5[9]; unsigned short hE; char pad10[4]; int n14; int n18; char pad1C[0xC]; };
extern int D_003DCF98;
extern int D_003DCF9C;
extern int D_003DCFF8;
extern struct E1 *D_003DCFFC;
extern int D_003DCFF0;
extern struct E2 *D_003DCFF4;
void __4GIFS(struct DMAS *);
void __4VIFS(struct X *);
struct M *__10STACKSCOPE(struct M *);
void _$_10STACKSCOPE(struct M *, int);
void AllocSw__4DMASi(struct X *, int);
void AddDmaCnt(struct X *) asm("AddDmaCnt__4DMAS");
void AddVifFlush(struct X *) asm("AddVifFlush__4VIFS");
void Reset(struct DMAS *) asm("Reset__4DMAS");
void AllocStatic(struct DMAS *, int, void *) asm("AllocStatic__4DMASiP2QW");
int func_00170548(struct BS *, int);
void func_001EC9D0(struct E1 *, int);
void BuildClutGifs(struct E1 *, int, struct DMAS *) asm("BuildClutGifs__FP4CLUTiP4GIFS");
void BuildBmpTex0(struct E2 *, int) asm("BuildBmpTex0__FP3BMPi");
void func_001ECBF0(struct E2 *, int, struct DMAS *);
void Detach(struct DMAS *, int *, int *) asm("Detach__4DMASPiPP2QW");
void AddVifDirect(struct X *, int, int, int) asm("AddVifDirect__4VIFSiP2QWi");
void AddVifDirectRefs(struct X *, int, int, int) asm("AddVifDirectRefs__4VIFSiP2QWi");
void AddPrimPack(struct DMAS *, int, int, int) asm("AddPrimPack__4GIFSiiUl");
void PackAD(struct DMAS *, int, int) asm("PackAD__4GIFSll");
void AddPrimEnd(struct DMAS *) asm("AddPrimEnd__4GIFS");
void EndDmaCnt(struct X *) asm("EndDmaCnt__4DMAS");
void AddDmaRet(struct X *) asm("AddDmaRet__4DMAS");
void DetachCopySw__4DMASPiPP2QWT2(struct X *, int, int, int *);
int func_001ECE58(struct BS *pbs, int k)
{
    struct DMAS dmas;
    struct X x;
    struct M m;
    char ab[0xA0];
    int cb, pv;
    int result;
    int n4;
    int i, j;
    __4GIFS(&dmas);
    result = 0;
    __4VIFS(&x);
    n4 = pbs->n4;
    __10STACKSCOPE(&m);
    AllocSw__4DMASi(&x, (D_003DCF9C * 3 + D_003DCF98) * 10 + 4);
    AddDmaCnt(&x);
    AddVifFlush(&x);
    for (i = 0; i < D_003DCFF8; i++) {
        struct E1 *pe = &D_003DCFFC[i];
        int v;
        if (pe->b4 != k)
            continue;
        Reset(&dmas);
        AllocStatic(&dmas, 10, ab);
        v = func_00170548(pbs, pe->hA);
        func_001EC9D0(pe, v);
        BuildClutGifs(pe, v, &dmas);
        *(ulong *)(dmas.pqw - 1) |= 0x8000;
        Detach(&dmas, &cb, &pv);
        AddVifDirect(&x, cb, pv, 0);
        AddVifDirectRefs(&x, pe->n10, pe->nC, 0);
    }
    for (j = 0; j < D_003DCFF0; j++) {
        struct E2 *pe = &D_003DCFF4[j];
        int v;
        if (k != pe->b4)
            continue;
        Reset(&dmas);
        AllocStatic(&dmas, 10, ab);
        v = func_00170548(pbs, pe->hE);
        BuildBmpTex0(pe, v);
        func_001ECBF0(pe, v, &dmas);
        *(ulong *)(dmas.pqw - 1) |= 0x8000;
        Detach(&dmas, &cb, &pv);
        AddVifDirect(&x, cb, pv, 0);
        AddVifDirectRefs(&x, pe->n18, pe->n14, 0);
    }
    if (n4 < pbs->n4) {
        Reset(&dmas);
        AllocStatic(&dmas, 10, ab);
        AddPrimPack(&dmas, 0, 1, 14);
        PackAD(&dmas, 0x3F, 0);
        AddPrimEnd(&dmas);
        Detach(&dmas, &cb, &pv);
        AddVifDirect(&x, cb, pv, 0);
        AddVifFlush(&x);
        EndDmaCnt(&x);
        AddDmaRet(&x);
        DetachCopySw__4DMASPiPP2QWT2(&x, 0, 0, &result);
    }
    {
        int r = result;
        _$_10STACKSCOPE(&m, 2);
        return r;
    }
}
