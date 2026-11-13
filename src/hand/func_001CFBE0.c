typedef int qword __attribute__((mode(TI)));
struct C { char pad[0x60]; void *p60; };
struct B { char pad[0xEC]; struct C *pc; };
struct A { int x0; struct B *pb; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int n);
int FBounceRip__FP3RIPP2SOG9VU_VECTORT2(void *p, struct A *pa, qword q0, qword q1);
void RemoveRip(void *p) asm("RemoveRip__FP3RIP");
int FBounceShrapnel__FP8SHRAPNELP2SOP6VECTORT2(void *p, struct A *pa, qword q0, qword q1)
{
    void *plo = pa->pb->pc->p60;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, 0x32)) return 0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, 0x59)) {
        RemoveRip(p);
        return 1;
    }
    return FBounceRip__FP3RIPP2SOG9VU_VECTORT2(p, pa, q0, q1);
}
