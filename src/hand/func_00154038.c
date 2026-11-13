/* class: DETECTOR (SafeHouse detect.cpp, orig 0x00154038: a watched target's requested state, when it has an entry). */
struct DETECTOR;
struct DETENTRY;
struct DETENTRY *PdetentryFind__FP8DETECTORi(struct DETECTOR *pdet, void *plo);
void SetDetentryState__FP8DETECTORP8DETENTRYi(struct DETECTOR *pdet, struct DETENTRY *pentry, int state);

void func_00154038(struct DETECTOR *pdet, void *plo, int state)
{
    struct DETENTRY *pentry = PdetentryFind__FP8DETECTORi(pdet, plo);
    if (pentry != 0) {
        SetDetentryState__FP8DETECTORP8DETENTRYi(pdet, pentry, state);
    }
}
