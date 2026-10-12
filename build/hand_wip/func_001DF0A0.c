typedef int qword __attribute__((mode(TI)));
typedef struct { int a, b; } S8;
typedef struct { float x, y, z; } __attribute__((aligned(16))) VECTOR;
typedef struct { char pad[0x148]; char x148[8]; } E;
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
extern S8 D_002A7AC0;
void func_001F5990(OBJ *, Q *);
void func_001DEF98(OBJ *, E *, qword *, float *);
int func_0014C6A0(Q *, qword, qword, int, HIT *);
int func_00132B10(void *, int);
int func_00205670(void *, qword, qword, qword *);
void func_001A7C18(void *, void *, Q *, qword, qword, int, qword, int, float, void *);
void func_00149AB8(void *, void *, S8, void *);
void func_001DF0A0(OBJ *p, Q *q)
{
    int i;
    func_001F5990(p, q);
    for (i = 0; i < p->x198; i++) {
        E *e = &p->x19C[i];
        qword out[2];
        VECTOR pos;
        HIT hit;
        int f = 0;
        func_001DEF98(p, e, out, 0);
        if (!func_0014C6A0(q, out[0], out[1], 1, &hit)) {
            void *so = *q->x4->x14;
            if (func_00132B10(so, 0x33))
                f = func_00205670(so, out[0], out[1], (qword *)&pos);
        } else {
            f = 1;
            *(qword *)&pos = hit.pos;
        }
        if (f) {
            qword d, t, dir, len;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(out[0]), "j"(*(qword *)&pos));
            __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(t));
            __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(dir) : "j"(out[1]), "j"(out[0]));
            __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(len), "=&j"(t) : "j"(dir));
            __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(len));
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(dir) : "j"(len), "j"(dir));
            func_001A7C18(D_003DD490, p->xE4, q, *(qword *)&pos, dir, 0xA, d, 0, 0.0f, e->x148);
            func_00149AB8(D_003DD490, p, D_002A7AC0, 0);
        }
    }
}
