/* class: CID_3F, a step guard kind (vt slot 15 = PostLoad; SafeHouse guardstart.cpp: after the step guard's post-load,
 * +0x1010 = a new class 3 object, oid 0x62B: its aim point). */
struct SW;
struct LO;
struct GUARD3F {
    /* 0x0000 */ char pad0[0x1010];
    /* 0x1010 */ struct LO *plo1010;   /* field: SafeHouse port - its aim point */
};
void PostStepguardLoad__FP9STEPGUARD(struct GUARD3F *pguard);
struct LO *PloNew__F3CIDP2SW3OIDi(int cid, struct SW *psw, int oid, int n);

void func_0014B1D8(struct GUARD3F *pguard)
{
    PostStepguardLoad__FP9STEPGUARD(pguard);
    pguard->plo1010 = PloNew__F3CIDP2SW3OIDi(3, 0, 0x62B, -1);
}
