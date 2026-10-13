typedef int qword __attribute__((mode(TI)));
union U { qword q; float f; };
struct M4 { qword row[4]; };
class B {
public:
    int a,b,c;
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void Set29(qword);
    virtual void Set30(const M4 &);
    virtual M4 *Get31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void Set35(qword);
    virtual void Set36(qword);
};
struct P : public B {
    char pad[0x208 - 0x10]; int count;
    char pad2[0x240 - 0x20C]; qword offset;
    char pad3[0x1048 - 0x250]; float amount;
    char pad4[0x1060 - 0x104C]; qword adjusted;
};
extern qword D_002A2DD0, D_002A2DC0;
extern "C" int func_00132B10(B *, int);
extern "C" void func_001F49C8(P *, B *);
static inline qword Scalar(float f) {
    qword r;
    __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f));
    return r;
}
static inline qword ScalarBits(int bits) {
    qword r;
    __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(bits));
    return r;
}
static inline qword Scale(qword v,qword f) {
    qword r;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v),"j"(f));
    return r;
}
static inline qword Load(const qword *p) {
    qword r;
    __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*p));
    return r;
}
static inline qword Transform(const M4 &m, qword v) {
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=&j"(r) : "j"(m.row[0]), "j"(m.row[1]), "j"(m.row[2]), "j"(m.row[3]), "j"(v));
    return r;
}
extern "C" void func_002052E0(P *p, B *other)
{
    if (other && func_00132B10(other, 3)) {
        M4 m;
        U scale;
        const M4 *source = other->Get31();
        m.row[0] = Load(&source->row[0]);
        m.row[1] = Load(&source->row[1]);
        m.row[2] = Load(&source->row[2]);
        m.row[3] = Load(&source->row[3]);
        scale.q = Scalar(-1.0f);
        p->Set29(Transform(m,Scale(p->offset,scale.q)));
        p->Set30(m);
        if (func_00132B10(p,0x34)) {
            scale.q = ScalarBits(*(int *)&p->amount);
            qword r = m.row[3];
            __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(r) : "j"(D_002A2DC0), "j"(scale.q));
            p->adjusted = r;
        }
        p->Set35(D_002A2DD0);
        p->Set36(D_002A2DD0);
        p->count = 0;
    } else {
        func_001F49C8(p,other);
    }
}
