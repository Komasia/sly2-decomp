// DRAFT (Claude agent): 190/240. Emitter particle batch add (PRG/BLK with 6 x 43-qword arrays, double-buffered). Logic complete; target keeps k in a stack slot and uses &a2[i] (pd) as the induction base; loop shape (b to k<c test) differs.
typedef int qword __attribute__((mode(TI)));
struct EMITTER;
struct PD { int n0; int n4; float g8; float gC; };
struct PAIR { qword a; qword b; };
struct BLK {
    qword a0[43]; qword a1[43]; qword a2[43];
    qword b0[43]; qword b1[43]; qword b2[43];
    char pad[0x1084 - 0x1020];
    int c; PAIR *apair; int pad108C; BLK *pblkNext;
};
struct PRG;
struct PRGVT { char pad[0x198]; short d; short pad2; void (*pfn)(PRG *, EMITTER *); };
struct PRG {
    char pad0[0xC]; PRGVT *pvt; char pad10[0x160 - 0x10]; int k160; char pad164[0x1A0 - 0x164]; int c1A0;
    char pad1A4[0x3B0 - 0x1A4]; int c3B0; char pad3B4[0x434 - 0x3B4]; int f434; int pad438; int k43C; int pad440;
    int c444; BLK *pblkFirst;
};
struct LM { float gMin, gMax; };
struct EMITTER { char pad[0xC8]; int fC8; char padCC[0xF0 - 0xCC]; int kF0; int fF4; LM lm; };
struct EMITX { PRG **ppprg; void *ppripg; EMITTER *pemitter; };
struct CM { char pad[0x70]; qword dir; };
extern "C" {
extern CM D_002DDF40;
extern char D_003DD490[];
PRG *func_001390D8(void *pv);
void func_001394C8(PRG *pprg, EMITTER *p);
BLK *func_00138FF8(void *pv, PRG *pprg);
void *func_002333B4(void *pv, int b, int cb);
int func_0011D3F8(int nMin, int nMax);
float func_0011D448(float gMin, float gMax);
void func_0015B428(EMITTER *p, EMITX *px, int c, qword *apos, qword *av, float *ag1, float *ag2, qword *aa, qword *ab);
}

static inline float Dot(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

void func_0015B428(EMITTER *p, EMITX *px, int c, qword *apos, qword *av, float *ag1, float *ag2, qword *aa, qword *ab)
{
    PRG *pprg = 0;
    if (px && px->ppprg)
        pprg = *px->ppprg;
    if (!pprg) {
        pprg = func_001390D8(D_003DD490);
        if (!pprg)
            return;
        if (px && px->ppprg)
            *px->ppprg = pprg;
        func_001394C8(pprg, p);
        if (px && px->pemitter)
            pprg->pvt->pfn((PRG *)((char *)pprg + pprg->pvt->d), px->pemitter);
        if (!pprg)
            return;
    }
    BLK *pblk = pprg->pblkFirst;
    int k = 0;
    for (;;) {
        if (k >= c)
            return;
        if (!pblk) {
            pblk = func_00138FF8(D_003DD490, pprg);
            if (!pblk)
                return;
        }
        for (unsigned int i = pblk->c; i < 43 && k < c; i++, k++) {
            pblk->a0[i] = apos[k];
            ((float *)&pblk->a0[i])[3] = ag1[k];
            pblk->a1[i] = av[k];
            ((float *)&pblk->a1[i])[3] = ag2[k];
            PD *pd = (PD *)&pblk->a2[i];
            func_002333B4(pd, 0, sizeof(qword));
            pd->n0 = func_0011D3F8(0, pprg->c3B0 - 1);
            if (pprg->f434)
                pd->n0 &= ~1;
            if (p->fC8)
                pd->n4 = func_0011D3F8(0, pprg->c1A0 - 1);
            if (pprg->k43C == 2) {
                float g = func_0011D448(p->lm.gMin, p->lm.gMax);
                pd->g8 = g;
                if (!p->kF0 && 0.0f < Dot(D_002DDF40.dir, pblk->a1[i]))
                    pd->g8 = -g;
                if (p->fF4)
                    pd->gC = func_0011D448(-3.14159265f, 3.14159265f);
            }
            if (pprg->k160 == 2) {
                PAIR *ppair = &pblk->apair[i];
                ppair->a = aa[k];
                ppair->b = ab[k];
            }
            pblk->b0[i] = pblk->a0[i];
            pblk->b1[i] = pblk->a1[i];
            pblk->b2[i] = pblk->a2[i];
            pblk->c++;
            pprg->c444++;
        }
        pblk = pblk->pblkNext;
    }
}
