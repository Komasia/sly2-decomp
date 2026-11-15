/* PxpCloneList (0x1AA020): a copy of a list of contacts, each new XP (0xC0 bytes) from the world's contact slot heap
 * (SW +0x3D40), in the same order. SafeHouse mark.cpp. */
typedef int qword __attribute__((mode(TI)));
typedef struct XP { union { qword q[12]; struct { char pad[0xAC]; struct XP *pxpNext; } s; } u; } XP;
struct SW { char pad[0x3D40]; char slotheapXp[1]; };
XP *func_0011CCC0(void *pslotheap);
// name: SafeHouse port (PxpCloneList)
XP *PxpCloneList__FP2XPPv(struct SW *psw, XP *pxpSrc)
{
    XP *pxpFirst;
    XP **ppxp;
    if (!pxpSrc)
        return 0;
    pxpFirst = 0;
    ppxp = &pxpFirst;
    do {
        XP *pxpNew = func_0011CCC0(psw->slotheapXp);
        *pxpNew = *pxpSrc;
        *ppxp = pxpNew;
        pxpSrc = pxpSrc->u.s.pxpNext;
        ppxp = &pxpNew->u.s.pxpNext;
    } while (pxpSrc);
    return pxpFirst;
}
