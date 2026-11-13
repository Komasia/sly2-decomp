/* ReleaseAsega: drop a reference to an animation segment player; the last one frees it: its two DL links are
 * unlinked (func_00256EE0 / func_002580A8), its controllers are let go (func_001334A8) and it goes back to the slot
 * heap of ASEGAs (D_003E1224). */
#include "asega.h"

struct SLOTHEAP;
extern struct SLOTHEAP D_003E1224;   /* the ASEGAs' slot heap */
void func_00256EE0(void *pv, int n);
void func_002580A8(void *pv, int n);
void func_001334A8(ASEGA *pasega);
void func_0011CD98(struct SLOTHEAP *pslotheap, void *pv);

// name: SafeHouse port (ReleaseAsega)
void ReleaseAsega__FP5ASEGAi(ASEGA *pasega, int n)
{
    int cref = pasega->cref - 1;
    pasega->cref = cref;
    if (cref <= 0) {
        func_00256EE0(pasega, 0);
        func_002580A8((char *)pasega + 4, 0);
        func_001334A8(pasega);
        func_0011CD98(&D_003E1224, pasega);
    }
}
