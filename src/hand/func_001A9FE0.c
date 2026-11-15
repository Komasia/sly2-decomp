/* PrependXpList (0x1A9FE0): puts a list of contacts (linked by XP +0xAC) in front of *ppxpHead. SafeHouse mark.cpp. */
struct XP { char pad[0xAC]; struct XP *pxpNext; };
// name: SafeHouse port (PrependXpList)
void PrependXpList__FP2XPPP2XPPv(void *psw, struct XP *pxpFirst, struct XP **ppxpHead)
{
    if (pxpFirst) {
        struct XP *pxpLast = pxpFirst;
        while (pxpLast->pxpNext) pxpLast = pxpLast->pxpNext;
        pxpLast->pxpNext = *ppxpHead;
        *ppxpHead = pxpFirst;
    }
}
