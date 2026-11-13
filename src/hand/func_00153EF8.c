/* class: DETECTOR (SafeHouse detect.cpp / detect.h, orig 0x153EF8: an object watched, the owner excluded). */
struct DETECTOR;
struct LO;
void AddDetectorTarget__FP8DETECTORP2LO(struct DETECTOR *pdet, struct LO *plo);

void func_00153EF8(struct DETECTOR *pdet, struct LO *ploOwner, struct LO *plo)
{
    if (ploOwner != plo) {
        AddDetectorTarget__FP8DETECTORP2LO(pdet, plo);
    }
}
