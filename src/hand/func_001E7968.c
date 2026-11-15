/* func_001E7968: rope option 1043's setter (EOPID 1209): the rope's second end on object plo (SafeHouse rope.cpp). */
struct ROPE;
struct LO;
struct ROPE *PropeEnsure__FP2LOi(void *ppath, int f);
void SetRopeEnd__FP4ROPEiP2LO(struct ROPE *prope, int iend, struct LO *plo);
void func_001E7968(void *ppath, struct LO *plo)
{
    SetRopeEnd__FP4ROPEiP2LO(PropeEnsure__FP2LOi(ppath, 1), 1, plo);
}
