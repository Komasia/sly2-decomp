/* func_001E7930: rope option 1042's setter (EOPID 1208): the rope's first end on object plo (SafeHouse rope.cpp). */
struct ROPE;
struct LO;
struct ROPE *PropeEnsure__FP2LOi(void *ppath, int f);
void SetRopeEnd__FP4ROPEiP2LO(struct ROPE *prope, int iend, struct LO *plo);
void func_001E7930(void *ppath, struct LO *plo)
{
    SetRopeEnd__FP4ROPEiP2LO(PropeEnsure__FP2LOi(ppath, 1), 0, plo);
}
