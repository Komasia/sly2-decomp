typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct S4C { char pad[0x148]; long fl; };
struct A { char pad[0x40]; int x40; char pad2[0x4C-0x44]; struct S4C *x4c; char pad3[0x60-0x50]; qword x60; char pad4[0x88-0x70]; float x88; };
struct O { char pad[0x208]; struct A *x208; char pad2[0x9E0-0x20C]; char x9e0[0x108C-0x9E0]; int x108c; };
struct T { char pad[0xEC]; int xec; char pad2[0x10C-0xF0]; float x10c; char pad3[0x184-0x110]; float x184; char pad4[0x19C-0x188]; int x19c; };
struct P { struct O *x0; int x4; int x8; int pad[2]; struct T *x14; void *x18; int x1c; float x20; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct T *t, int n);
void RecordSafeTarget__FP5ACTORP2LOf(void *p, void *s, float g);
void RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR(void *p, int a, qword q);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
// name: SafeHouse port (UpdateSafeInteract)
void UpdateSafeInteract__FP5ACTOR(struct P *p)
{
    float g, s;
    switch (p->x8) {
    case 3:
        if (p->x14->x19c)
            return;
        g = p->x20;
        RecordSafeTarget__FP5ACTORP2LOf(p->x0->x9e0, p->x18, g);
        break;
    case 4:
        if (p->x14->xec)
            return;
        g = 0.0f;
        RecordSafeTarget__FP5ACTORP2LOf(p->x0->x9e0, p->x18, g);
        break;
    case 0:
    case 13:
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x14, 0xC)) {
            if (p->x14->x19c)
                return;
            g = p->x20;
            RecordSafeTarget__FP5ACTORP2LOf(p->x0->x9e0, p->x18, g);
            break;
        }
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x14, 0x26)) {
            if (p->x14->xec)
                return;
            g = 0.0f;
            RecordSafeTarget__FP5ACTORP2LOf(p->x0->x9e0, p->x18, g);
            break;
        }
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->x14, 0x22)) {
            if (p->x14->xec)
                return;
            s = p->x14->x10c;
        } else
            s = p->x14->x184;
        {
            qword a;
            U d;
            a = PosOfLo__FP2LO(p->x0);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d.q) : "j"(a), "j"(PosOfLo__FP2LO(p->x14)));
            g = atan2f(d.f[1], d.f[0]) * s;
        }
        RecordSafeTarget__FP5ACTORP2LOf(p->x0->x9e0, p->x18, g);
        break;
    default:
    {
        struct O *o = p->x0;
        struct A *pa = o->x208;
        if (pa && pa->x88 > 0.7f && !(pa->x4c->fl & 0x20000000) && !o->x108c)
            RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR(o->x9e0, pa->x40, pa->x60);
        return;
    }
    }
}
