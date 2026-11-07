typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; int (*pfn)(void *); };
struct SO { char pad[0xC]; struct VTE *vt; char pad1[0x240 - 0x10]; qword pos; char pad2[0x11AC - 0x250]; int x11AC; };
struct L { int x0; struct L *pNext; int x8; struct SO *pso; };
struct C { char pad[0x64]; struct L *pl; };
struct T { char pad[0xE4]; struct C *pc; void *xE8; void *xEC; int xF0; int xF4; int xF8; };
struct W { char pad[0xEC]; void *xEC; char pad1[0x130 - 0xF0]; struct W *pNext; };
struct BUF { char a[0x180]; };
extern char g_sw[];
extern struct W *D_003E1480;
void *PloPlayerPo__FP2SW(void *p);
int func_001A61A0(struct SO *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int k);
int func_0020F1B8(void *p);
qword PosOfLo__FP2LO(struct SO *p);
qword PosDetectorEye__FP8DETECTOR(struct T *p);
qword ConvertPos__FP2LOT0G9VU_VECTOR(int z, struct W *pw, qword v);
int ClipSegmentBsp__FP6BSPREFP6VECTORG9VU_VECTORT2iP3LSG(void *p, int mask, qword a, qword b, int n, struct BUF *pbuf);
int FPointInShape__FP2LOG9VU_VECTOR(void *p, qword v);
int FTargetHidden__FP8DETECTORP2LO(struct T *p, struct SO *pso);
int FSightBlocked__FP8DETECTORP2LO(struct T *p, struct SO *pso);
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }

// name: SafeHouse port (NDetectState)
int NDetectState__FP8DETECTORP2LOi(struct T *p, struct SO *pso, int k)
{
    struct BUF buf;
    qword v;
    struct W *pw;
    struct SO *pme = PloPlayerPo__FP2SW(g_sw);
    if (!pso) { k = 0; goto done; }
    if (!func_001A61A0(pso)) { k = 0; goto done; }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pso, 0x32) && pso->vt[77].pfn((char *)pso + pso->vt[77].d) == 2) { k = 0; goto done; }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pso, 0x34) && pme && FIsBasicDerivedFrom__FP5BASIC3CID(pme, 0x46)) { k = 0; goto done; }
    if (func_0020F1B8(g_sw)) { k = 0; goto done; }
    if (p->xF4) { k = 0; goto done; }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pso, 0x34) && pso->x11AC) { k = 0; goto done; }
    if (p->xF0) { k = 1; goto done; }
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pso, 0x33))
        v = Add(PosOfLo__FP2LO(pso), pso->pos);
    else
        v = PosOfLo__FP2LO(pso);
    for (pw = D_003E1480; pw; pw = pw->pNext) {
        qword a = ConvertPos__FP2LOT0G9VU_VECTOR(0, pw, PosDetectorEye__FP8DETECTOR(p));
        qword b = ConvertPos__FP2LOT0G9VU_VECTOR(0, pw, v);
        if (ClipSegmentBsp__FP6BSPREFP6VECTORG9VU_VECTORT2iP3LSG(pw->xEC, 0x7FFFFFFF, a, b, 4, &buf) > 0) { k = 0; goto done; }
    }
    switch (k) {
    case 0:
        if (p->pc) {
            struct L *pl;
            for (pl = p->pc->pl; pl; pl = pl->pNext) {
                if (pl->pso == pso) {
                    if (pl->x0) { k = 1; goto done; }
                    break;
                }
            }
        }
        if (!FPointInShape__FP2LOG9VU_VECTOR(p->xE8, v)) { k = 0; goto done; }
        if (p->xEC && !FPointInShape__FP2LOG9VU_VECTOR(p->xEC, v)) { k = 0; goto done; }
        if (!(p->xF8 & 1) && FTargetHidden__FP8DETECTORP2LO(p, pso)) { k = 0; goto done; }
        if (p->xF8 & 2) { k = 1; goto done; }
        { k = !FSightBlocked__FP8DETECTORP2LO(p, pso); goto done; }
    case 1:
        if (p->xEC && !FPointInShape__FP2LOG9VU_VECTOR(p->xEC, v)) { k = 0; goto done; }
        if (!FPointInShape__FP2LOG9VU_VECTOR(p->xE8, v)) { k = 2; goto done; }
        break;
    case 2:
        if (p->xEC && !FPointInShape__FP2LOG9VU_VECTOR(p->xEC, v)) { k = 0; goto done; }
        if (FPointInShape__FP2LOG9VU_VECTOR(p->xE8, v)) {
            if (p->xF8 & 2) { k = 1; goto done; }
            if (FSightBlocked__FP8DETECTORP2LO(p, pso)) return k;
            k = 1;
            goto done;
        }
        break;
    default:
        goto done;
    }
    if ((p->xF8 & 8) && FSightBlocked__FP8DETECTORP2LO(p, pso)) k = 0;
done:
    return k;
}
