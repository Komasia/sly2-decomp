/* class: SLOTHEAP (slotheap.h): one slot allocated and freed at once (0x11CCC0 / 0x11CD98), so the heap's first block
 * exists; StartSw does it for its slot heaps. */
#include "slotheap.h"

void *func_0011CCC0(SLOTHEAP *pslotheap);
void func_0011CD98(SLOTHEAP *pslotheap, void *pv);

void func_0011CDD8(SLOTHEAP *pslotheap)
{
    func_0011CD98(pslotheap, func_0011CCC0(pslotheap));
}
