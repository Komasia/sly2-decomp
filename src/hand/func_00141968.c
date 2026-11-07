typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct VTE { short d; short pad; void (*pfn)(void *, qword); };
struct E8 { char pad[0x80]; qword q; };
struct P {
    char pad0[0xC]; struct VTE *vt; char pad1[0xE8 - 0x10]; struct E8 *pE8;
    char pad2[0x248 - 0xEC]; float dz; char pad3[0x2E8 - 0x24C]; int f2E8; int f2EC; char pad4[0x2F4 - 0x2F0];
    float g2F4; char pad5[0x300 - 0x2F8]; int k300; char pad6[0x360 - 0x304]; UQ v360;
    char pad7[0xDF4 - 0x370]; int xDF4;
};
qword PosOfLo__FP2LO(struct P *p);
qword VecBallisticVelocity__FfG9VU_VECTORN21(qword a, qword b, float g, qword c);
void SetJumpKind__FP4JUMPiiP2LO(void *p, int a, int b, int c);
// name: SafeHouse port (LaunchActorTo)
void LaunchActorTo__FP5ACTORG9VU_VECTORff(struct P *p, qword v, float g, float h)
{
    UQ pos;
    UQ r;
    pos.q = PosOfLo__FP2LO(p);
    pos.f[2] += p->dz;
    r.q = VecBallisticVelocity__FfG9VU_VECTORN21(pos.q, v, g, p->pE8->q);
    p->vt[35].pfn((char *)p + p->vt[35].d, r.q);
    if (p->xDF4 == -1) {
        SetJumpKind__FP4JUMPiiP2LO((char *)p + 0x2C0, 8, 0, 0);
        p->k300 = 3;
        p->v360.q = r.q;
        p->v360.f[2] = 0.0f;
        p->g2F4 = h;
        if (h == p->v360.f[2]) {
            p->f2E8 = 0;
            p->f2EC = 0;
        }
    }
}
