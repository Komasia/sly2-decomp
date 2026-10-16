typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { float x,y,z; } VECTOR3;
typedef struct { qword row[3]; } M3;
union FLOATWORD { float value; int bits; };
extern int D_002DDED4;
struct O { char pad[0xB0]; qword angularVelocity; char pad2[0x30]; qword angularForce; };
struct S { char pad[0x5C]; struct O *po; char pad2[0x1A4 - 0x60]; int k; char pad3[8]; M3 desired; qword v1E0; char pad4[0x1F4 - 0x1F0]; float f1F4, f1F8, f1FC, f200; };
void func_001F9B20(struct S *p);
void func_001F59A0(struct S *,M3 *,VECTOR3 *);
static inline void InitScalar(U *value,int bits) {
    register qword scalar __asm__("vf4");
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(bits));
    value->q=scalar;
}
void func_00204108(struct S *p)
{
    func_001F9B20(p);
    switch (p->k) {
    case 0: {
        VECTOR3 v;
        float s = p->f200;
        v.z = p->f1FC;
        v.x = p->f1F4 * s;
        v.y = p->f1F8 * s;
        func_001F59A0(p, &p->desired, &v);
        break;
    }
    case 1: {
        register struct O *po __asm__("$3") = p->po;
        U u;
        register qword d __asm__("vf3");         register qword vel __asm__("vf2");
        vel = po->angularForce;
        d=p->v1E0;
        __asm__("vsub.xyzw %0,%0,%1" : "+j"(d) : "j"(po->angularVelocity));
        InitScalar(&u,D_002DDED4);
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(d) : "j"(u.q));
        __asm__("vadd.xyzw %0,%0,%1" : "+j"(vel) : "j"(d));
        po->angularForce=vel;
        break;
    }
    case -1:
        break;
    }
}
