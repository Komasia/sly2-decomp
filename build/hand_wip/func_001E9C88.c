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
    register int cpv __asm__("$21")=0;
    register void **ppv __asm__("$22");
    int cseg = 0;
    float tStart, tPrev, t, tEnd;
    void *pPrev;
    typedef char layout_local_segments[(sizeof(aseg)==0x200)?1:-1];
    typedef char layout_local_region_addresses[(sizeof(apv)==0x100)?1:-1];
    typedef char layout_local_point[(sizeof(pos)==16)?1:-1];
    typedef char layout_local_query_request_overlay[(sizeof(pos2)==16 && __alignof__(pos2)==16)?1:-1];

    ps->po = po;
    tStart = func_001E6620(po);
    tPrev = tStart;
    t = tStart;
    tEnd = func_001E6648(ps->po);
    func_001E6F10(ps->po, tStart, &pos, 0);
    pPrev = func_001C0D70(pos, 0);
    ppv = apv;
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
                { *ppv++ = pCur; cpv++; }
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

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_float[(sizeof(float)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_qword_align[(__alignof__(qword)==16)?1:-1];
typedef char layout_MSG[(sizeof(struct MSG)==8)?1:-1];
typedef char layout_SEG[(sizeof(struct SEG)==8)?1:-1];
typedef char layout_S_prefix[(sizeof(struct S)==0x9C)?1:-1];
typedef char layout_O_prefix[(sizeof(struct O)==0xF8)?1:-1];
typedef char layout_MSG_cb[((unsigned)&((struct MSG*)0)->cb==0x0)?1:-1];
typedef char layout_MSG_nKind[((unsigned)&((struct MSG*)0)->nKind==0x4)?1:-1];
typedef char layout_SEG_a[((unsigned)&((struct SEG*)0)->a==0x0)?1:-1];
typedef char layout_SEG_b[((unsigned)&((struct SEG*)0)->b==0x4)?1:-1];
typedef char layout_S_po[((unsigned)&((struct S*)0)->po==0x0)?1:-1];
typedef char layout_S_c4[((unsigned)&((struct S*)0)->c4==0x4)?1:-1];
typedef char layout_S_aseg[((unsigned)&((struct S*)0)->aseg==0x8)?1:-1];
typedef char layout_S_cC[((unsigned)&((struct S*)0)->cC==0xc)?1:-1];
typedef char layout_S_aseg10[((unsigned)&((struct S*)0)->aseg10==0x10)?1:-1];
typedef char layout_S_c90[((unsigned)&((struct S*)0)->c90==0x90)?1:-1];
typedef char layout_S_apv[((unsigned)&((struct S*)0)->apv==0x94)?1:-1];
typedef char layout_S_n98[((unsigned)&((struct S*)0)->n98==0x98)?1:-1];
typedef char layout_O_vt[((unsigned)&((struct O*)0)->vt==0xc)?1:-1];
typedef char layout_O_curved[((unsigned)&((struct O*)0)->curved==0xe0)?1:-1];
typedef char layout_O_fE4[((unsigned)&((struct O*)0)->fE4==0xe4)?1:-1];
typedef char layout_O_count[((unsigned)&((struct O*)0)->count==0xe8)?1:-1];
typedef char layout_O_parameters[((unsigned)&((struct O*)0)->parameters==0xec)?1:-1];
typedef char layout_O_distances[((unsigned)&((struct O*)0)->distances==0xf0)?1:-1];
typedef char layout_O_points[((unsigned)&((struct O*)0)->points==0xf4)?1:-1];
typedef char layout_S_inline_segment_span[(sizeof(((struct S*)0)->aseg10)==0x80)?1:-1];
