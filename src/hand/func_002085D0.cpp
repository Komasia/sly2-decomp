inline void *operator new(unsigned int,void *storage){return storage;}
#include "clock.h"
struct GUARD;
struct DETENTRY { struct GUARD *plo; int nState; float tSeen; int pad; DETENTRY(GUARD *ploSource,const CLOCK&clock):plo(ploSource),nState(0),tSeen(clock.t){} };
struct DETECTOR { char pad[0xFC]; unsigned int cdetentry; struct DETENTRY adetentry[8]; };
struct GUARD { char pad[0x3A4]; int cdetentryGenerated; char pad2[0xF64 - 0x3A8]; struct DETECTOR *pdet; };
extern "C" struct DETENTRY *PdetentryFind(struct DETECTOR *pdet, struct GUARD *plo) asm("PdetentryFind__FP8DETECTORi");
extern "C" void *s1_memmove(void *pvDst, void *pvSrc, int cb) asm("memmove");

/* func_002085D0 (0x2085D0): adds plo (not the guard itself) to the guard's detector entries unless it is already
 * there: with fFront at the end of the list; otherwise in front of the cdetentryGenerated generated entries (a full
 * list gives up its first generated one for it). The new entry starts in state 0, seen now. Returns whether it was
 * added. */
extern "C" int func_002085D0(struct GUARD *pguard, struct GUARD *plo, int fFront)
{
    struct DETENTRY *pdetentry;
    struct DETECTOR *pdet;
    register unsigned int ib __asm__("$16");
    if (!plo || plo == pguard)
        return 0;
    pdetentry = 0;
    if (!fFront)
        pdetentry = PdetentryFind(pguard->pdet, plo);
    if (!pdetentry) {
        pdet = pguard->pdet;
        ib = pdet->cdetentry;
        if (ib >= 8) {
            int cGen;
            if (!fFront) {
                cGen = pguard->cdetentryGenerated;
                if (cGen > 0) {
                    pguard->cdetentryGenerated = cGen - 1;
                    ib=8; ib-=cGen; ib*=16; ib+=0x100;
                    pdetentry=(struct DETENTRY*)((char*)pdet+ib);
                    s1_memmove(pdetentry + 1, pdetentry, (cGen - 1) * 16);
                    goto fill;
                }
            }
        } else {
            if (fFront) {
                register unsigned int offset __asm__("$2")=ib*16+0x100;
                pdetentry=(struct DETENTRY*)((char*)pdet+offset);
            } else {
                int cGen = pguard->cdetentryGenerated;
                ib-=cGen; ib*=16; ib+=0x100;
                pdetentry=(struct DETENTRY*)((char*)pdet+ib);
                s1_memmove(pdetentry + 1, pdetentry, cGen * 16);
            }
        fill:
            new(pdetentry) DETENTRY(plo,g_clock);
            pguard->pdet->cdetentry++;
            return 1;
        }
    }
    return 0;
}
