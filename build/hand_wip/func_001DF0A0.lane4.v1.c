typedef int qword __attribute__((mode(TI)));
typedef struct { short kind,index; union { short item; int value; } payload; } PAIR;
struct CONTACT;
typedef struct { int id,kind; char unknown8[8]; qword value; char unknown20[0x80]; } ENDPOINT;
typedef struct { ENDPOINT endpoint[2]; char unknown140[8]; struct CONTACT *head; int unknown14C; } E;
typedef struct {
    char pad0[0xE4];
    void *xE4;
    char pade8[0x198 - 0xE8];
    int x198;
    E *x19C;
} OBJ;
typedef struct { char pad[0x14]; void **x14; } SUB;
typedef struct { int x0; SUB *x4; } Q;
typedef struct { qword pos; char pad[0x50]; } HIT;
extern char D_003DD490[];
extern PAIR D_002A7AC0;
void func_001F5990(void);
void func_001DEF98(OBJ *,ENDPOINT *,qword *,float *);
int func_0014C6A0(Q *, qword, qword, int, HIT *);
int func_00132B10(void *, int);
int func_00205670(void *, qword, qword, qword *);
void func_001A7C18(void *,void *,Q *,qword,qword,int,long,int,struct CONTACT **,float);
void func_00149AB8(void *,void *,PAIR,int);
#define LEN 2
#define NRM 0
#define DIR 0
typedef union { qword q; float f[4]; } VECTOR;
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword SubIn(qword a, qword b) { __asm__("vsub.xyzw %0, %0, %1" : "+j"(a) : "j"(b)); return a; }
#if LEN == 0
static inline qword Len(qword v)
{
    qword d;
    __asm__("vmul.xyz %0, %1, %1\n\tvaddw.x $vf3, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf3, %0z" : "=j"(d) : "j"(v) : "vf3");
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
#elif LEN == 1
static inline qword Len(qword v)
{
    qword d;
    __asm__("vmul.xyz %0, %1, %1\n\tvaddw.x $vf3, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf3, %0z" : "=j"(d) : "j"(v) : "vf3");
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
#elif LEN == 2
static inline qword Len(qword v)
{
    qword d;
    __asm__("vmul.xyz %0, %1, %1\n\tvaddw.x $vf3, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf3, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(v) : "vf3");
    return d;
}
#elif LEN == 3
static inline qword Len(qword v)
{
    qword d;
    __asm__("vmul.xyz %0, %1, %1\n\tvaddw.x $vf3, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, $vf3, %0z" : "=j"(d) : "j"(v) : "vf3");
    __asm__("vsqrt $Q, %0x" : : "j"(d));
    __asm__("vwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d));
    return d;
}
#endif
#if NRM == 0
static inline qword Normalize(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
#else
static inline qword Normalize(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %0x" : : "j"(l));
    __asm__("vwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v));
    return r;
}
#endif
static inline long Bits(qword v) { return (long)v; }
void func_001DF0A0(OBJ *p, Q *q)
{
    int i;
    func_001F5990();
    for (i = 0; i < p->x198; i++) {
        register int stride __asm__("$2") = sizeof(E);
        E *e = (E*)((char*)p->x19C + i * stride);
        qword out[2];
        VECTOR pos;
        HIT hit;
        long f = 0;
        func_001DEF98(p,e->endpoint,out,0);
        if (!func_0014C6A0(q, out[0], out[1], 1, &hit)) {
            void *so = *q->x4->x14;
            if (func_00132B10(so, 0x33))
                f = func_00205670(so, out[0], out[1], &pos.q);
        } else {
            f = 1;
            pos.q = hit.pos;
        }
        if (f) {
            qword d = Len(Sub(out[0], pos.q));
#if DIR == 0
            qword dir = Sub(out[1], out[0]);
#else
            qword dir = SubIn(out[1], out[0]);
#endif
            long bits = Bits(d);
            qword l = Len(dir);
            qword nd = Normalize(dir, l);
            func_001A7C18(D_003DD490,p->xE4,q,pos.q,nd,0xA,bits,0,&e->head,0.0f);
            func_00149AB8(D_003DD490, p, D_002A7AC0, 0);
        }
    }
}
