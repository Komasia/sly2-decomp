/* StopK2 (0x20C080): a kind-2 player not yet done is set done (K2ST_Done) and its ASEGA (+0x38) let go. */
#include "h6_guard.h"
#define OFS_K2PLAY_PASEGA 0x38
int FK2Done(char *pk2play) asm("FK2Done__FP6K2PLAY");
void SetK2State__FP6K2PLAYi(char *pk2play, int st);
void ApplyAsegCur(int paseg, int palo, int grf, void *ppasega, float t, float uWeight) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
// name: SafeHouse port (StopK2)
void StopK2__FP6K2PLAY(char *pk2play) { if (!FK2Done(pk2play)) { SetK2State__FP6K2PLAYi(pk2play, K2ST_Done); ApplyAsegCur(0, 0, 0, pk2play + OFS_K2PLAY_PASEGA, 0.0f, 1.0f); } }
