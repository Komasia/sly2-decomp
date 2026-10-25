/* func_001DF0A0: for every segment entry of p, find where the segment's two endpoints hit the request (first
   func_0014C6A0, else the shape test func_00132B10 + func_00205670) and add a kind-10 contact there with PxpAdd
   (func_001A7C18), then post the D_002A7AC0 notification.
   - Same 6-argument virtual signature as func_001823C8 / func_0013ADE8: the base stub func_001F5990 gets all the
     arguments passed through (no code, but the call's argument uses fix the prologue schedule).
   - Len = Sqrt(Dot(v, v)) with a two-input Dot, one asm per VU step (this gives the target's VU order and vf regs).
   - The distance is a float in a GPR (qmfc2) passed bit-for-bit as PxpAdd's int argument. */
typedef int qword __attribute__((mode(TI)));
typedef struct { short kind, index; union { short item; int value; } payload; } PAIR;
struct CONTACT;
typedef struct { int id, kind; char unknown8[8]; qword value; char unknown20[0x80]; } ENDPOINT;
typedef struct { ENDPOINT endpoint[2]; char unknown140[8]; struct CONTACT *head; int unknown14C; } ENTRY;
typedef struct {
    char pad0[0xE4];
    void *shape;
    char padE8[0x198 - 0xE8];
    int entryCount;
    ENTRY *entries;
} OBJ;
typedef struct { char pad[0x14]; void **x14; } SUB;
typedef struct { int x0; SUB *x4; } REQUEST;
typedef struct { qword pos; char pad[0x50]; } HIT;
typedef union { qword q; float f[4]; } VECTOR;
extern char D_003DD490[];
extern PAIR D_002A7AC0;
void func_001F5990(OBJ *, REQUEST *, int, int, int, struct CONTACT **);
void func_001DEF98(OBJ *, ENDPOINT *, qword *, float *);
int func_0014C6A0(REQUEST *, qword, qword, int, HIT *);
int func_00132B10(void *, int);
int func_00205670(void *, qword, qword, qword *);
void func_001A7C18(void *, void *, REQUEST *, qword, qword, int, int, int, struct CONTACT **, float);
void func_00149AB8(void *, void *, PAIR, int);

static inline qword Sub(qword a, qword b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword Sqrt(qword d)
{
    qword l;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Len(qword v) { return Sqrt(Dot(v, v)); }
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline float Scalar(qword v)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v));
    return f;
}

void func_001DF0A0(OBJ *p, REQUEST *q, int a2, int a3, int a4, struct CONTACT **pout)
{
    int i;
    func_001F5990(p, q, a2, a3, a4, pout);
    for (i = 0; i < p->entryCount; i++) {
        /* register pin: the stride is set inside the loop as in the target, so loop.c does not strength-reduce
           i * sizeof(ENTRY) (the target keeps the mult in the loop) */
        register int stride __asm__("$2") = sizeof(ENTRY);
        ENTRY *e = (ENTRY *)((char *)p->entries + i * stride);
        qword seg[2];
        VECTOR pos;
        HIT hit;
        int found = 0;
        func_001DEF98(p, e->endpoint, seg, 0);
        if (!func_0014C6A0(q, seg[0], seg[1], 1, &hit)) {
            void *so = *q->x4->x14;
            if (func_00132B10(so, 0x33))
                found = func_00205670(so, seg[0], seg[1], &pos.q);
        } else {
            found = 1;
            pos.q = hit.pos;
        }
        if (found) {
            float dist = Scalar(Len(Sub(seg[0], pos.q)));
            qword dir = Sub(seg[1], seg[0]);
            dir = Div(dir, Len(dir));
            func_001A7C18(D_003DD490, p->shape, q, pos.q, dir, 10, *(int *)&dist, 0, &e->head, 0.0f);
            func_00149AB8(D_003DD490, p, D_002A7AC0, 0);
        }
    }
}
