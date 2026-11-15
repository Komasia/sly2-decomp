/* func_001711F0: the marker command (op 9) of an oid in a command list, or 0. */
#include "h2_cmdlist.h"
struct CMDLIST { char pad[0x50]; CMD *pcmdFirst; };
CMD *func_001711F0(struct CMDLIST *pcmdlist, int oid) { int unused[4]; CMD *pcmd; for (pcmd = pcmdlist->pcmdFirst; pcmd; pcmd = pcmd->pcmdNext) if (pcmd->op == CMDOP_Marker && pcmd->oid == oid) break; return pcmd; }
