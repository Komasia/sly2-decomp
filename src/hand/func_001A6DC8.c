/* func_001A6DC8 (0x1A6DC8): sets byte +0x2D of an LO and passes the value to each of its children (+0x64 list,
 * linked by +0x24) that does not have bit 58 of +0x28 set (func_001A6D28). */
typedef unsigned long ulong;
struct O { char pad[0x24]; struct O *pNext; ulong grf; char pad2[0x34]; struct O *pFirst; };
void func_001A6D28(struct O *, int);
void func_001A6DC8(struct O *plo, int b)
{
    struct O *ploChild;
    *((unsigned char *)plo + 0x2D) = b;
    for (ploChild = plo->pFirst; ploChild; ploChild = ploChild->pNext) {
        if (!(ploChild->grf & (1UL << 58)))
            func_001A6D28(ploChild, b);
    }
}
