// v3 (Claude agent, laneC13 2026-10-23): v2 + 60 empty asms at the end (EXPERIMENT, not a final form). The 5 spill slots 0x4E64-0x4E74 follow the pseudo numbers of gcse PRE reaching regs, which are handed out in expression-hash-bucket order; bucket = (C + sp offset) mod S with S = max_cuid/2|1 (171 here). ~60 more insns at gcse time (S 201/203) give the target order. Still aligned 9: rgba lui sched, a3/a1 for 0x10, t0/a3 for D_003DD040.
extern "C" {
struct BIS;
struct AREQ { int cb; int cbAlign; };
void func_001AE478(void *p);
void func_001AE4A0(void *p, int n);
void *func_001AE1D0(AREQ *preq);
void *func_001AE2A0(AREQ *preq);
void *func_001AE318(AREQ *preq);
void func_001AE5A0(void *pvDst, void *pvSrc, int cb);
void *func_002333B4(void *pv, int b, int cb);
void func_0012AE18(void);
int func_00117D50(BIS *pbis);
int func_00117DB8(BIS *pbis);
void func_00117968(BIS *pbis, int cb, void *pv);
void func_00117988(BIS *pbis, int cb);
void func_001C9058(void *p);
void func_001C9090(void *p, void *pv);
void func_001C9098(void *p);
void func_001FD0E8(void *p, BIS *pbis);
void func_001FD5E8(void *p);
void func_001D7B88(void *p, BIS *pbis);
void func_0020F318(void *psw, BIS *pbis);
void func_0013DF80(void *psw, BIS *pbis);
void func_0013E0E0(void *psw, BIS *pbis);
void func_0013F810(void *p, BIS *pbis);
void func_001FF7E8(void *psw);
void func_0020E3C0(void *psw);
void func_0020F1C8(void *psw);
void func_0016F960(void *p, void *pv, int c);
void func_001703F8(void *pzpr, int a, int b);
void func_001ED3A8(void);
void func_001ED448(void);
void func_001EA9F0(void *psw, void *pzpr);
void func_00258248(void *p);
void *func_0014B690(void *p);
void func_001848A8(void *p, int k, void *pv, int n);
void func_00184950(void *p, int n);
void func_0020F5D0(int n, BIS *pbis);
void func_001FF858(void *psw, int n, BIS *pbis);
void func_001EB748(void *pa, void *pb, BIS *pbis);
void func_001C0EC0(void *psw, BIS *pbis);
struct LO;
struct LOL { void *pvt; int x4; int c; LO **apo; };
LOL *func_0013F888(LOL *p);
void func_0013FB40(int n, BIS *pbis, LOL *p);
void func_001EC7A0(void);
LO *func_0013E510(LO *po, int n);
extern char D_002A4BD0[];
extern char D_003DD040[];
extern char D_003DD490[];
extern char D_002DDF40[];
extern char D_002DEDC0[];
extern int D_003E1C34;
}
struct VTE { short d; short pad; void (*pfn)(); };
struct LO { int pad[3]; VTE *pvt; };
struct WE {
    int c0; LO **apo; int c8; int cC; int x10; int x14; void *pv18; char ab1C[0x40]; int x5C; int x60; int pad64[2];
};
struct RGBA { unsigned char r, g, b, a; };
struct SW {
    char pad0[0x39D0]; void *p39D0; int x39D4; void *p39D8; int x39DC; void *p39E0; void *p39E4; int x39E8;
    char pad39EC[0x3E00 - 0x39EC]; RGBA rgba; char pad3E04[0x3E38 - 0x3E04]; int x3E38;
    char pad3E3C[0x3F04 - 0x3E3C]; int cwe; WE *awe; int pad3F0C; int iwe;
};
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct ZPR { char ab[0x630]; };
struct ODD { ODD() { ab[2] = 2; } int ab[0x110 / 4]; };
class OBJ { public: OBJ(int k, void *pv, int n); ~OBJ(); char ab[0x70]; };
static inline void *AllocZ(AREQ *preq, int cb) { preq->cb = cb; preq->cbAlign = 0x10; return func_001AE2A0(preq); }
static inline void *Alloc(AREQ *preq, int cb) { preq->cb = cb; preq->cbAlign = 0x10; return func_001AE1D0(preq); }
static inline void *AllocS(AREQ *preq, int cb) { preq->cb = cb; preq->cbAlign = 0x10; return func_001AE318(preq); }

extern "C" void func_0013DA18(SW *psw, BIS *pbis)
{
    union { AREQ req; RGBA rgba; struct { int pad[2]; int c; LO **apo; } lol; } u;
    int i;
    func_0012AE18();
    psw->cwe = func_00117D50(pbis);
    psw->awe = (WE *)AllocZ(&u.req, psw->cwe * 0x6C);
    int h;
    func_001C9058(&h);
    func_001C9090(&h, D_002A4BD0);
    for (i = 0; i < psw->cwe; i++) {
        WE *pwe = &psw->awe[i];
        func_00117968(pbis, 0x40, pwe->ab1C);
        pwe->x5C = func_00117DB8(pbis);
        pwe->x60 = func_00117DB8(pbis);
        pwe->x10 = func_00117DB8(pbis);
        pwe->x14 = func_00117DB8(pbis);
        pwe->c8 = func_00117DB8(pbis);
        pwe->pv18 = Alloc(&u.req, pwe->c8 * 4);
        func_002333B4(pwe->pv18, -1, pwe->c8 * 4);
    }
    func_001FD0E8(D_003DD040, pbis);
    func_001D7B88((char *)psw + 0x3A18, pbis);
    func_0020F318(psw, pbis);
    func_0013DF80(psw, pbis);
    func_0013E0E0(psw, pbis);
    func_0013F810(D_003DD490, pbis);
    func_0013F810(D_002DDF40, pbis);
    func_00117988(pbis, 0x10);
    func_001FF7E8(psw);
    func_0020E3C0(psw);
    func_0020F1C8(psw);
    if (psw->x3E38)
        *(int *)&psw->rgba = 0x80000000;
    u.rgba = psw->rgba;
    func_0016F960(D_002DEDC0, &u.rgba, 3);
    psw->p39E4 = psw->p39E0 = AllocS(&u.req, 0x10000);
    psw->p39D0 = AllocS(&u.req, 0x6000);
    psw->x39D4 = 0;
    psw->p39D8 = AllocS(&u.req, 0x3000);
    psw->x39DC = 0;
    FRAME frame;
    ZPR zpr0;
    ZPR zpr1;
    func_001703F8(&zpr0, 0x1800, 0x4000);
    func_001ED3A8();
    func_001703F8(&zpr1, 0x1000, 0x1800);
    func_001EA9F0(psw, &zpr0);
    for (i = 0; i < psw->cwe; ) {
        WE *pwe = &psw->awe[i];
        int iNext = i + 1;
        ODD odd;
        char ab[0x4040];
        func_00258248(&odd);
        func_001C9090(&h, func_0014B690(pwe->ab1C));
        psw->iwe = pwe->x5C ? -1 : i;
        OBJ obj(0x403F, ab, 0);
        func_0020F5D0(1, pbis);
        D_003E1C34 = func_00117DB8(pbis);
        func_001FF858(psw, pwe->x10, pbis);
        func_001EB748(&zpr0, &zpr1, pbis);
        func_001C0EC0(psw, pbis);
        {
            FRAME frameT;
            int j, k;
            LO **ppo;
            AREQ req2;
            func_0013F888((LOL *)&u.lol);
            func_0013FB40(0, pbis, (LOL *)&u.lol);
            func_00117988(pbis, 0x10);
            func_0014B690(pwe->ab1C);
            func_001EC7A0();
            psw->x39E8 = 0;
            pwe->c0 = u.lol.c;
            pwe->apo = (LO **)AllocZ(&req2, pwe->c0 * pwe->c8 * 4);
            func_001AE5A0(pwe->apo, u.lol.apo, pwe->c0 * 4);
            ppo = &pwe->apo[pwe->c0];
            for (j = 1; j < pwe->c8; j++)
                for (k = 0; k < pwe->c0; k++)
                    *ppo++ = func_0013E510(pwe->apo[k], 0);
            if (pwe->x5C) {
                pwe->cC++;
            } else {
                for (k = 0; k < pwe->c8 * pwe->c0; k++) {
                    LO *po = pwe->apo[k];
                    ((void (*)(LO *))po->pvt[9].pfn)((LO *)((char *)po + po->pvt[9].d));
                }
            }
        }
        i = iNext;
    }
    func_001ED448();
    psw->iwe = -2;
    func_001FD5E8(D_003DD040);
    func_001C9090(&h, 0);
    func_001C9098(&h);
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
    __asm__ __volatile__("");
}
