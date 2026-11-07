struct S { char *p0; char pad[0x64]; void *x68; };
void *PloNew__F3CIDP2SW3OIDi(int, int, int, int);
void SetZoneForced__FP2LOi(void *, int);
void ResetZoneInteract__FP2LO(struct S *);
void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(char *, void *, void *);
void BindGait__FP4GAIT(void *);
void func_00137A30(char *, int, int, void *, int, int, int, void *);
void func_001CC5E8(void *, char *, char *);
// name: SafeHouse port (PostLoadInteract)
void PostLoadInteract__FP5ACTOR(struct S *p) {
    char *pb = (char *)p;
    p->x68 = PloNew__F3CIDP2SW3OIDi(0xF, 0, 0x148, -1);
    SetZoneForced__FP2LOi(p->x68, 0);
    ResetZoneInteract__FP2LO(p);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p->p0, pb + 0x70, pb + 0x170);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(p->p0, pb + 0x330, pb + 0x430);
    BindGait__FP4GAIT(pb + 0x180);
    BindGait__FP4GAIT(pb + 0x240);
    func_00137A30(p->p0, 0xC, 3, pb + 0x2F0, 0, 0, 0, pb + 0x314);
    func_001CC5E8(pb + 0x440, p->p0, p->p0 + 0x1030);
}
