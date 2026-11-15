/* func_001DFAD8: Init of a relay (SCPT; relay.h, SafeHouse scpt.cpp): the LO init, no command limit set yet (-1: the
 * default 0x200), and an empty list of its running scripts (JSGs, linked at JSG::dleRelay +0xE4). */
#include "relay.h"
void InitLo__FP2LO(RELAY *prelay);
void InitDl__FP2DLi(DL *pdl, int ibDle);
void func_001DFAD8(RELAY *prelay) {
    InitLo__FP2LO(prelay);
    prelay->crelaycmdMax = -1;
    InitDl__FP2DLi(&prelay->dlJsg, 0xE4);
}
