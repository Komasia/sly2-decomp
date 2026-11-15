/* func_001E79F0: rope option 1044's setter (EOPID 1210): the rope's length (SetRopeLength) (SafeHouse rope.cpp). */
struct ROPE;
struct ROPE *PropeEnsure__FP2LOi(void *ppath, int f);
void SetRopeLength__FP4ROPEf(struct ROPE *prope, float s);
void func_001E79F0(void *ppath, float s)
{
    SetRopeLength__FP4ROPEf(PropeEnsure__FP2LOi(ppath, 1), s);
}
