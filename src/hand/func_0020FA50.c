/* func_0020FA50 (0x20FA50): 0x20FA10's filter, keeping only entries of still objects (their vt slot 62). */
#include "vtbl.h"
struct ALOV { int unk_0x00, unk_0x04, unk_0x08; VTENT *pvt; };
struct SOE { int unk_0x00; struct ALOV *palo; };
int func_0020FA10(void *pvFilter, struct SOE *psoe);
int func_0020FA50(void *pvFilter, struct SOE *psoe) { struct ALOV *palo; VTENT *pvte; if (!func_0020FA10(pvFilter, psoe)) return 0; palo = psoe->palo; pvte = &palo->pvt[62]; return ((int (*)(void *))pvte->pfn)(VT_THIS(palo, pvte)); }
