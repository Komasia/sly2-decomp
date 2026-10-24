/* laneG7v1 (Claude agent): aligned 28 (from laneG6v1 30, no pins). The D_002BF340/344 broadcasts are two volatile qmtc2 asms (the VU_FLOAT ctor's own instruction, volatile so sched1 can't sink them) written into plain qword locals and copied into VU_FLOAT lo/hi, declared before the pos computation: gives the target's vf8/vf7 and the desired reuse in vf2. Left: they now issue before Transform (target: after Transform / after the center store; non-volatile forms get sunk by sched1 and allocate vf3/vf2), neg.s f0 vs f22, 1300B8 arg order on the 2nd call.
   was: laneG6v1 (Claude agent): fresh clean rewrite, no pins, aligned 30 (codex18v1 27 used 10+ pins and lui/lw/lqc2 asms). VU_FLOAT by-value temps give the 0x40 scalar slot; desired is a spilled qword (0x130). Floats-after-P* 1300B8 prototype (30; real-order prototype 32). Left: target keeps the low/high broadcasts in vf8/vf7 (live across Transform) and reuses desired in vf2 for the high offset (ours reloads it: one extra lqc2); neg.s into f0 (ours f22). */
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; } U;
struct M4 { U row[4]; };
struct LSG { U position[2], normal[2]; float parameter[2]; int tag48; void *owner; void *plane; int pad[3]; };
struct MODEL { char pad[0x14]; void *table; };
struct SELECTOR { char pad[0x30]; MODEL *model; };
struct P {
    char pad[0x60]; void *context;
    char pad64[0x1030 - 0x64]; MODEL *model; SELECTOR *selector;
    char pad1038[0x18C8 - 0x1038]; int manual;
    char pad18CC[0x18D8 - 0x18CC]; int state;
    int reserved18DC; MODEL *other;
};
struct AUX { void *component; char pad4[0xA0 - 4]; U point; char padB0[0x10]; float radius0, radius1; };
struct O { char pad[0xA8]; AUX *aux; };
struct CACHE { void *table; int present; float radius; int reserved; U desired, center, hit0, hit1, end; };
extern "C" {
extern U D_002A2DC0;
extern float D_002BF340, D_002BF344;
float *func_0012F938(void *, int);
void func_001300B8(void *, P *, float, float, void *, void *, M4 *, M4 *);
int func_0014C748(qword, float, qword, qword, int, LSG *);
}
struct VU_FLOAT { qword q; VU_FLOAT() {} VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Transform(M4 *m, qword pt)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
        : "=j"(r) : "0"(m->row[0].q), "j"(m->row[1].q), "j"(m->row[2].q), "j"(m->row[3].q), "j"(pt));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }

extern "C" void func_00189C40(P *p, void *first, float height, O *second, void *unused, CACHE *cache)
{
    MODEL *model;
    if (!p->manual) {
        if (p->state < 6) goto standard;
        if (p->state < 10) { model = p->other; goto have; }
        if (p->state >= 14) goto standard;
        if (p->state < 12) goto standard;
        model = p->other; goto have;
standard:
        model = p->selector->model;
    } else if (p->selector) {
        model = p->selector->model;
    } else {
        model = p->model;
    }
have:
    if (model->table == cache->table) return;
    cache->table = model->table;
    float offset = 0.0f;
    float *pv = func_0012F938(model->table, 0x16A);
    if (pv) offset = *pv;
    float zero = 0.0f;
    M4 m0;
    func_001300B8(model->table, p, offset, zero, first, p->context, &m0, 0);
    qword desired = AddScaled(m0.row[3].q, D_002A2DC0.q, VU_FLOAT(-height));
    M4 m1;
    func_001300B8(model->table, p, offset, zero, second, p->context, &m1, 0);
    M4 m2;
    func_001300B8(model->table, p, offset, zero, second->aux->component, p->context, &m2, 0);
    LSG hit;
    qword qlo, qhi; __asm__ volatile("qmtc2.ni %1, %0" : "=j"(qlo) : "r"(*(int *)&D_002BF340)); __asm__ volatile("qmtc2.ni %1, %0" : "=j"(qhi) : "r"(*(int *)&D_002BF344)); VU_FLOAT lo, hi; lo.q = qlo; hi.q = qhi;
    qword pos = Add(m1.row[3].q, Sub(desired, Transform(&m2, second->aux->point.q)));
    cache->center.q = pos;
    cache->radius = second->aux->radius0 + second->aux->radius1 + 10.0f;
    cache->present = func_0014C748(pos, cache->radius,
        AddScaled(desired, D_002A2DC0.q, lo),
        AddScaled(desired, D_002A2DC0.q, hi), 1, &hit) > 0;
    cache->hit0 = hit.position[0];
    cache->desired.q = desired;
    cache->hit1 = hit.position[1];
    cache->end.q = AddScaled(cache->center.q, D_002A2DC0.q, VU_FLOAT(-cache->radius));
}
