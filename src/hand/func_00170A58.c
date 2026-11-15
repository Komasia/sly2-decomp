/* PostLoadCmdlist: after the load, each path command's path (found from the current near object) that is a plain
 * path is made usable by the AI (func_001E9C30); near-object commands move the context. */
struct G;
extern struct G g_sw;
#include "h2_cmdlist.h"
struct LO { char pad[0x50]; CMD *pcmdFirst; };   /* CMDLIST: its commands */
struct LO *PloFindSwNearest__FP2LO3OIDii(struct G *psw, int grf, int oid, struct LO *ploCtx);
int func_001709A8(struct LO *ppath);
void func_001E9C30(struct LO *ppath);
// name: SafeHouse port (PostLoadCmdlist)
void PostLoadCmdlist__FP7CMDLIST(struct LO *plo) {
    CMD *pcmd;
    for (pcmd = plo->pcmdFirst; pcmd; pcmd = pcmd->pcmdNext) {
        switch (pcmd->op) {
        case CMDOP_Path: {
            struct LO *ppath = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, pcmd->oid, plo);
            if (ppath && func_001709A8(ppath) == -1) func_001E9C30(ppath);
            break;
        }
        case CMDOP_Near:
            plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, plo ? 4 : 5, pcmd->oid, plo);
            break;
        }
    }
}
