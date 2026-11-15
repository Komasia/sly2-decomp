/* PrunNew: creates a script (JSG / RUN, relay.h) on the relay starting at the BlockBegin command prelaycmdFirst: a
 * zeroed JSG from its slot heap D_003E1560 with the JSG vtable, the context object of the script that started it (or
 * the relay itself), the block's labelled object, and the block's matching BlockEnd as its last command (nested
 * blocks counted; an unclosed block runs just its first command). It is put on the relay's script list and gets
 * its first reference (vt slot 1). */
#include "relay.h"
extern char D_003E1560[];          /* JSG slot heap */
extern char g_sw[];
extern VTENT D_002D8C08[];         /* JSG vtable */
JSG *func_0011CCC0(void *pslotheap);   /* slot heap alloc */
void *s1_memset(void *, int, int) asm("memset");
LO *PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, OID oid, int);
void PrependDlEntry__FP2DLPv(DL *pdl, void *pv);
// name: SafeHouse port (PrunNew)
JSG *PrunNew__FP2LOPvP3RUN(RELAY *prelay, RELAYCMD *prelaycmdFirst, JSG *pjsgParent)
{
    JSG *pjsg = func_0011CCC0(D_003E1560);
    RELAYCMD *prelaycmdLast, *prelaycmd;
    int cdepth;
    s1_memset(pjsg, 0, sizeof(JSG));
    pjsg->basic.pframe = 0;
    pjsg->basic.psidebag = 0;
    pjsg->basic.pvt = D_002D8C08;
    pjsg->psnd = 0;
    pjsg->prelay = prelay;
    if (pjsgParent)
        pjsg->ploContext = pjsgParent->ploContext;
    else
        pjsg->ploContext = (LO *)prelay;
    if (prelaycmdFirst->u.blockBegin.oidLabel != -1)
        pjsg->ploBlock = PloFindSwNearest__FP2LO3OIDii(g_sw, 5, prelaycmdFirst->u.blockBegin.oidLabel, 0);
    pjsg->prelaycmdFirst = prelaycmdFirst;
    prelaycmdLast = &prelay->arelaycmd[prelay->crelaycmd - 1];
    cdepth = 1;
    for (prelaycmd = prelaycmdFirst + 1; prelaycmd <= prelaycmdLast; prelaycmd++) {
        switch (prelaycmd->relayck) {
        case RELAYCK_BlockBegin:
            cdepth++;
            break;
        case RELAYCK_BlockEnd:
            cdepth--;
            if (cdepth == 0) {
                pjsg->prelaycmdLast = prelaycmd;
                goto done;
            }
            break;
        }
    }
    pjsg->prelaycmdLast = pjsg->prelaycmdFirst;
done:
    PrependDlEntry__FP2DLPv(&prelay->dlJsg, pjsg);
    ((void (*)(void *))pjsg->basic.pvt[1].pfn)(VT_THIS(pjsg, &pjsg->basic.pvt[1]));
    return pjsg;
}
