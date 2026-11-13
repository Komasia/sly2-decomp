/* class: DETECTOR (SafeHouse detect.cpp: its flag 4's filter, 0x154528 - the class-0x31 objects only). */
struct SWENTRY {
    /* 0x0 */ int pad0;
    /* 0x4 */ void *plo;
};
int func_0020FA10(void *pv, struct SWENTRY *pentry);
int func_00132EA0(void *plo);   /* the object's class id */

int func_00154528(void *pv, struct SWENTRY *pentry)
{
    if (func_0020FA10(pv, pentry) == 0) {
        return 0;
    }
    return func_00132EA0(pentry->plo) == 0x31;
}
