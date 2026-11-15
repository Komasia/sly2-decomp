/* PloFind: looks up an object by oid for a script (JSG), nearest to the script's context object; a proxy (CID_PROXY)
 * resolves to the object it stands for (func_001CB2E0). -1: none. */
#include "relay.h"
#include "cid.h"
extern struct G g_sw;
void *PloFindSwNearest__FP2LO3OIDii(struct G *psw, int grffso, OID oid, LO *ploContext);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
void *func_001CB2E0(void *pproxy);
// name: SafeHouse port (PloFind)
void *PloFind__FP3RUNi(JSG *pjsg, OID oid)
{
    void *plo;
    if (oid == -1) {
        plo = 0;
    } else {
        plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, oid, pjsg->ploContext);
        if (plo && FIsBasicDerivedFrom__FP5BASIC3CID(plo, CID_PROXY)) plo = func_001CB2E0(plo);
    }
    return plo;
}
