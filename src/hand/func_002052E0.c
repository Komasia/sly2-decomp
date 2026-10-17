/* (Claude agent) func_002052E0: copy source matrix row by row, -1 broadcast via plain qmtc2 helper (no volatile asm);
   the dead store of the scale union is written just before the position call so it lands in the jalr delay slot. */
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f; } U;
typedef union {float value;int word;} FLOATWORD;
typedef struct M4 { qword row[4]; } M4;
typedef struct {short delta,unused; void (*fn)();} VTE;
typedef struct B {int a,b,c; VTE *vt;} B;
typedef struct P {
    B base;
    char pad[0x208 - 0x10]; int count;
    char pad2[0x240 - 0x20C]; qword offset;
    char pad3[0x1048 - 0x250]; FLOATWORD amount;
    char pad4[0x1060 - 0x104C]; qword adjusted;
} P;
extern qword D_002A2DD0, D_002A2DC0;
extern int func_00132B10(B *, int);
extern void func_001F49C8(P *, B *);
static inline qword Transform(const M4 *m, qword v) {
    register qword r __asm__("vf7");
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "+&j"(r) : "j"(m->row[0]), "j"(m->row[1]), "j"(m->row[2]), "j"(m->row[3]), "j"(v));
    return r;
}
static inline qword Broadcast(float f){register qword r __asm__("vf6");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword MulX(qword v,qword s){register qword r __asm__("vf2");__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
extern void func_002052E0(P *p, B *other)
{
    if (!other) return;
    if (func_00132B10(other, 3)) {
        M4 m;
        U scale;
        register qword v __asm__("vf2");
        register VTE *set __asm__("a2");
        VTE *get = &other->vt[31];
        const M4 *source = ((M4 *(*)(B *))get->fn)((B *)((char *)other+get->delta));
        m.row[0] = source->row[0];
        set = p->base.vt;
        {qword sc = Broadcast(-1.0f);
        m.row[1] = source->row[1];
        v = MulX(p->offset, sc);
        m.row[2] = source->row[2];
        m.row[3] = source->row[3];
        {qword t = Transform(&m,v);
        P *self = (P *)((char *)p+set[29].delta);
        register void (*positionFn)(P*,qword) __asm__("v1")=(void(*)(P*,qword))set[29].fn;
        scale.q = sc;
        positionFn(self, t);}}
        { VTE *s=p->base.vt; ((void (*)(P *,const M4 *))s[30].fn)((P *)((char *)p+s[30].delta), &m); }
        if (func_00132B10(&p->base,0x34)) {
            qword r;
            __asm__("qmtc2.ni %1,%0" : "=j"(scale.q) : "r"(p->amount.word));
            r = m.row[3];
            __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(r) : "j"(D_002A2DC0), "j"(scale.q));
            p->adjusted = r;
        }
        { VTE *s=p->base.vt; ((void (*)(P *,qword))s[35].fn)((P *)((char *)p+s[35].delta), D_002A2DD0); }
        { VTE *s=p->base.vt; ((void (*)(P *,qword))s[36].fn)((P *)((char *)p+s[36].delta), D_002A2DD0); }
        p->count = 0;
    } else {
        func_001F49C8(p,other);
    }
}
