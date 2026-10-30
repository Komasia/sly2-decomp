typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VTE { short delta; short pad; void *fn; };
struct SPACE { M4 matrix; char pad40[0x54]; int kind; char pad98[8]; SPACE *parent; };
struct LO { char padC[0xC]; VTE *vt; char pad10[0x50]; SPACE *space; };
struct SOURCE { char padC[0xC]; VTE *vt; };
struct MOTION { char pad74[0x74]; float duration; };
struct PATH { char padC[0xC]; VTE *vt; char pad10[0xD0]; int mode; int pad;int count; float *times; float *distances; qword *points; };
struct BLEND { float weight; MOTION *motion; int flags; PATH *first; PATH *second; };
struct P { LO *owner; void *animation; BLEND blends[2]; MOTION *controller; SOURCE *source; SPACE *space; int word3C; M4 matrix; };
struct REQUEST { int size; int alignment; REQUEST(int cb) { size = cb; alignment = 16; } };
extern "C" {
extern int D_002C1ED0;
M4 *func_0011C168(M4 *, const M4 *, const M4 *);
PATH *func_0013E3C8(int, LO *, int, int);
void *func_001AE1D0(const REQUEST &);
void *func_002333B4(void *, int, int);
void func_001300B8(MOTION *, LO *, SPACE *, SPACE *, M4 *, M4 *, float, float);
void func_001E6180(PATH *);
void func_00137A30(LO *, int, int, BLEND *, int, void *, void *, MOTION **);
}
static inline qword TransformPoint(const M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]), "j"(v));
    return r;
}
extern "C" void func_001CC5E8(P *p, LO *owner, void *animation)
{
    M4 original;
    p->owner = owner;
    p->animation = animation;
    SOURCE *source = p->source;
    if (!source) return;
    SPACE *originalSpace = ((SPACE *(*)(SOURCE *, M4 *))source->vt[32].fn)((SOURCE *)((char *)source + source->vt[32].delta), &original);
    p->matrix = original;
    p->space = originalSpace;
    while (p->space->kind != 6) {
        M4 product;
        func_0011C168(&product, &p->space->matrix, &p->matrix);
        p->matrix = product;
        p->space = p->space->parent;
    }
    int present = 0;
    for (int i = 0; i < 2; i++) {
        MOTION *motion = p->blends[i].motion;
        if (!motion) continue;
        PATH **first = &p->blends[i].first;
        PATH **second = &p->blends[i].second;
        present++;
        for (int j = 0; j < 2; j++) {
            PATH *path = func_0013E3C8(10, p->owner, 0xB2, -1);
            path->mode = 0;
            path->count = D_002C1ED0;
            path->times = (float *)func_001AE1D0(REQUEST(D_002C1ED0 * 4));
            path->distances = (float *)func_001AE1D0(REQUEST(D_002C1ED0 * 4));
            path->points = (qword *)func_001AE1D0(REQUEST(D_002C1ED0 * 16));
            M4 working;
            SPACE *space;
            if (j == 0) {
                working = original;
                space = originalSpace;
            } else {
                space = p->space;
                func_002333B4(&working, 0, sizeof(M4));
                ((float *)&working)[0] = ((float *)&working)[5] = ((float *)&working)[10] = ((float *)&working)[15] = 1.0f;
            }
            M4 sample;
            for (int k = 0; k < D_002C1ED0; ) {
                float t = (float)k / (float)(D_002C1ED0 - 1);
                func_001300B8(motion, p->owner, space, p->owner->space, &sample, 0, t * motion->duration, 0.0f);
                path->times[k] = t;
                path->points[k] = TransformPoint(&sample, working.r[3]);
                k++;
            }
            ((void (*)(PATH *))path->vt[9].fn)((PATH *)((char *)path + path->vt[9].delta));
            func_001E6180(path);
            if (j == 0) *first = path; else *second = path;
        }
    }
    if (present == 2) {
        p->blends[0].weight = 1.0f;
        func_00137A30(p->owner, 20, 2, p->blends, 0, 0, 0, &p->controller);
    }
}
