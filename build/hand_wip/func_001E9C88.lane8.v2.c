/* lane8 v2: no pins, aligned 22: store-first q[cpv++] (code shape = target, but s6/s7/fp rotated; see build/lane_notes/lane8.md). */
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct SEG { float a, b; };
struct O { char padC[0xC]; void *vt; char pad10[0xE0-0x10]; int curved; int fE4; int count; float *parameters; float *distances; qword *points; };
struct S { struct O *po; int c4; struct SEG *aseg; int cC; struct SEG aseg10[16]; int c90; void **apv; int n98; };
extern float D_002C367C;
float func_001E6620(struct O *);
float func_001E6648(struct O *);
void func_001E6F10(struct O *, float, qword *, qword *);
void *func_001C0D70(qword, int);
int func_001C0920(void *, qword, int);
void *func_001AE238(struct MSG *, void *);
void func_001AE5A0(void *, const void *, unsigned);
void func_001E9C88(struct S *ps, struct O *po)
{
    struct SEG aseg[64];
    void *apv[64];
    qword pos;
    qword pos2;
    struct SEG *pseg = 0;
    int cpv = 0;
    void **q = apv;
    int cseg = 0;
    float tStart, tPrev, t, tEnd;
    void *pPrev;

    ps->po = po;
    tStart = func_001E6620(po);
    tPrev = tStart;
    t = tStart;
    tEnd = func_001E6648(ps->po);
    func_001E6F10(ps->po, tStart, &pos, 0);
    pPrev = func_001C0D70(pos, 0);
    for (; t < tEnd; t += D_002C367C) {
        void *pCur;
        int outside;
        func_001E6F10(ps->po, t, &pos2, 0);
        pCur = func_001C0D70(pos2, 0);
        if (pCur) {
            int i;
            for (i = 0; i < cpv; i++)
                if (apv[i] == pCur)
                    break;
            if (i >= cpv && (unsigned)cpv < 64)
                q[cpv++] = pCur;
        }
        outside = 0;
        if (!pCur || pPrev != pCur || !func_001C0920(pPrev, pos2, 0))
            outside = 1;
        if (outside) {
            if (!pseg && cseg < 64) {
                pseg = &aseg[cseg++];
                pseg->a = tPrev;
            }
        } else if (pseg) {
            pseg->b = t;
            pseg = 0;
        }
        tPrev = t;
        pPrev = pCur;
    }
    if (pseg)
        pseg->b = tEnd;
    if (cseg >= 2 && ps->po->fE4 && aseg[0].a == tStart && aseg[cseg - 1].b == tEnd) {
        aseg[0].a = aseg[cseg - 1].a - tEnd;
        aseg[cseg - 1].b = aseg[0].b + tEnd;
    }
    {
        ps->c4 = cseg;
        ((struct MSG *)&pos2)->cb = cseg * 8;
        ((struct MSG *)&pos2)->nKind = 0x10;
        ps->aseg = func_001AE238((struct MSG *)&pos2, aseg);
        ps->cC = cseg;
        func_001AE5A0(ps->aseg10, aseg, cseg * 8);
        ps->c90 = cpv;
        ((struct MSG *)&pos2)->cb = cpv * 4;
        ((struct MSG *)&pos2)->nKind = 0x10;
        ps->apv = func_001AE238((struct MSG *)&pos2, apv);
        ps->n98 = -1;
    }
}
