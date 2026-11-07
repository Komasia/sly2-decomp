typedef int ti128 __attribute__((mode(TI)));
struct S { char pad[0x10b8]; int f10b8; char pad2[0x1320 - 0x10bc]; char a1320[0xc0]; char a13e0[0x100]; char a14e0[0x10];
    char a14f0[0x100]; char a15f0[0x10]; char a1600[0x110]; char a1710[0x10]; };
extern ti128 D_002BC920;
void func_001400B8(struct S *);
int func_001F4C58(struct S *, int, int);
void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(struct S *, void *, void *);
void BindGait__FP4GAIT(void *);
void InitBentleySub__FP10BENTLEYSUBP3ALOG9VU_VECTORff(void *, struct S *, ti128, float, float);
void AttachActorLook__FP5ACTORi(struct S *, int);
void SetBentleyState__FP7BENTLEYi(struct S *, int);
// name: SafeHouse port (PostLoadBentley)
void PostLoadBentley__FP7BENTLEY(struct S *p) {
    func_001400B8(p);
    p->f10b8 = func_001F4C58(p, 0xb, 1);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, p->a13e0, p->a14e0);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, p->a14f0, p->a15f0);
    BindGait__FP4GAIT(p->a1320);
    BindGait__FP4GAIT(p->a1600);
    InitBentleySub__FP10BENTLEYSUBP3ALOG9VU_VECTORff(p->a1710, p, D_002BC920, -50.0f, 50.0f);
    AttachActorLook__FP5ACTORi(p, 0x16);
    SetBentleyState__FP7BENTLEYi(p, 0);
}
