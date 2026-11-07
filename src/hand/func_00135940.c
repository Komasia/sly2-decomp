typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VT { short d; short pad; void *pfn; };
struct P { char pad[0xC]; struct VT *pvt; char pad1[0x2C0 - 0x10]; char a2C0[0x200]; char a4C0[0xDF0 - 0x4C0];
    char aDF0[0x160]; char aF50[0x13D0 - 0xF50]; int k; char pad3[0x16B0 - 0x13D4]; int x16B0; };
extern float D_002BC990;
void ApplyAloGravity__FP3ALO(struct P *p);
void UpdateStepPhysMotion__FP3ALO(struct P *p);
void func_00196DF8(void *p);
void func_00194170(void *p);
void UpdateDamageMotion__FP5ACTOR(void *p);
void func_0019DF70(void *p);
void AccelAloPos__FP3ALOG9VU_VECTOR(struct P *p, qword v);
// name: SafeHouse port (UpdateBentleyMotion)
void UpdateBentleyMotion__FP3ALO(struct P *p)
{
    if (p->k == 13)
        ApplyAloGravity__FP3ALO(p);
    else
        UpdateStepPhysMotion__FP3ALO(p);
    switch (p->k) {
    case 2: func_00196DF8(p->a2C0); break;
    case 3: func_00194170(p->a4C0); break;
    case 4: UpdateDamageMotion__FP5ACTOR(p->aDF0); break;
    case 13: func_0019DF70(p->aF50); break;
    case 6:
        if (p->x16B0 == 2) {
            register struct VT *vt __asm__("$3") = p->pvt;
            U a, u;
            qword v, r, q;
            qword (*pfn)(void *) = (qword (*)(void *))vt[33].pfn;
            short d = vt[33].d;
            __asm__("mfc1 %0, %1" : "=r"(q) : "f"(-D_002BC990));
            a.q = q;
            u.q = q;
            v = pfn((char *)p + d);
            __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "0"(u.q), "j"(v));
            AccelAloPos__FP3ALOG9VU_VECTOR(p, r);
        }
        break;
    }
}
