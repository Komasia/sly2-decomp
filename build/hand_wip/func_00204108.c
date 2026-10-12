/* 10 diffs: structure identical; only vf/GPR register numbering in case 1 differs (cf. func_0020BB58) */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { float x, y, z; } VECTOR3;
extern struct { float t; float dt; } D_002DDED0;
struct O { char pad[0xB0]; qword pos; char pad2[0x30]; qword vel; };
struct S { char pad[0x5C]; struct O *po; char pad2[0x1A4 - 0x60]; int k; char pad3[8]; char x1B0[0x1E0 - 0x1B0]; qword v1E0; char pad4[0x1F4 - 0x1F0]; float f1F4, f1F8, f1FC, f200; };
void func_001F9B20(struct S *p);
void func_001F59A0(struct S *p, void *pv, VECTOR3 *pw);
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
        func_001F59A0(p, p->x1B0, &v);
        break;
    }
    case 1: {
        struct O *po = p->po;
        U u;
        qword d, r, vel;
        vel = po->vel;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p->v1E0), "j"(po->pos));
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(*(int *)&D_002DDED0.dt));
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(d) : "j"(u.q));
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(vel), "j"(d));
        po->vel = r;
        break;
    }
    case -1:
        break;
    }
}
