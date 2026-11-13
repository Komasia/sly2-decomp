/* PtargetrecOf: the pursuit record of an object (0x1F8240), else a new one (0xAC bytes, 0x20A5F8).
 * Names: SafeHouse port (aipursuit.h). */
struct LO;
struct TARGETREC;
struct TARGETREC *func_001F8240(struct LO *plo);   /* SafeHouse: PtargetrecFind */
struct TARGETREC *func_0020A5F8(void *pv, struct LO *plo);   /* SafeHouse: TARGETREC::TARGETREC */
void *__builtin_new(unsigned int cb);

// name: SafeHouse port (PtargetrecOf)
struct TARGETREC *PtargetrecOf__FP2LO(struct LO *plo)
{
    struct TARGETREC *ptargetrec = func_001F8240(plo);
    if (ptargetrec)
        return ptargetrec;
    return func_0020A5F8(__builtin_new(0xAC), plo);
}
