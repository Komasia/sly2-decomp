/* StopK3 (0x20CA48): a directional player not yet done lets go of its ASEGA (+0x24). */
#define OFS_K3PLAY_PASEGA 0x24
int FK3Done(char *pk3play) asm("FK3Done__FP6K3PLAY");
void ApplyAsegCur(int paseg, int palo, int grf, void *ppasega, float t, float uWeight) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
// name: SafeHouse port (StopK3)
void StopK3__FP6K3PLAY(char *pk3play) { if (!FK3Done(pk3play)) ApplyAsegCur(0, 0, 0, pk3play + OFS_K3PLAY_PASEGA, 0.0f, 1.0f); }
