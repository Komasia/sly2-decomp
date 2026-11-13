/* class: CID_24, a use object (vt slot 51 = Use; SafeHouse interact.cpp: the base use, then Murray (cid 0x36) takes it,
 * 0x1B7000). */
struct LO;
void UseObjectBase__FP2LOi(struct LO *puse, struct LO *plo);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *pbasic, int cid);
void func_001B7000(struct LO *pmurray, struct LO *puse);   /* SafeHouse: MurrayTakeObject */

void func_00184330(struct LO *puse, struct LO *plo)
{
    UseObjectBase__FP2LOi(puse, plo);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, 0x36) != 0) {
        func_001B7000(plo, puse);
    }
}
