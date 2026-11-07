typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x18]; int x18; };
extern qword D_002A2DE0;
void PostLoadActorParts__FP5ACTOR(struct S *p);
void BindGait__FP4GAIT(void *p);
void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(struct S *p, void *a, void *b);
void func_0020BD88(void *p, struct S *s);
void PostLoadJtThrow__FP7JTTHROW(void *p);
void AttachActorLook__FP5ACTORi(struct S *p, int n);
void *func_001F4C58(struct S *p, int a, int b);
int PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct S *p, void *a, int b, int c, int d, qword q);
void func_001B6078(struct S *p, int n);
void PostMurrayLoad__FP6MURRAY(struct S *p)
{
    char *b = (char *)p;
    void *v;
    PostLoadActorParts__FP5ACTOR(p);
    BindGait__FP4GAIT(b + 0x1320);
    BindGait__FP4GAIT(b + 0x1460);
    BindGait__FP4GAIT(b + 0x1630);
    BindGait__FP4GAIT(b + 0x1540);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p, b + 0x16F0, b + 0x17F0);
    func_0020BD88(b + 0x1850, p);
    PostLoadJtThrow__FP7JTTHROW(b + 0x1910);
    AttachActorLook__FP5ACTORi(p, 0x16);
    v = func_001F4C58(p, p->x18, 0xC);
    if (v) {
        *(int *)(b + 0x1ACC) = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p, v, 0, 7, 2, D_002A2DE0);
    }
    func_001B6078(p, 0);
}
