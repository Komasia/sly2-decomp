/* class: CID_3C, a step guard kind (SafeHouse guard3c.cpp: the filter 0x1BA100 of its 0x20FAA0 search - class 0x62
 * objects). */
struct SWENTRY {
    /* 0x0 */ int pad0;
    /* 0x4 */ void *plo;
};
int func_00132EA0(void *plo);   /* the object's class id */

int func_001BA100(void *pv, struct SWENTRY *pentry)
{
    return func_00132EA0(pentry->plo) == 0x62;
}
