#include "qw.h"
struct CRITSECT { int a; };
struct GSDB { int a; };
extern CRITSECT D_002DFB40;
extern int D_002DEDB0;
extern GSDB D_002DEBD0, D_002DECC0;
extern int g_pdcGif;
extern "C" {
void EnterCritSect(CRITSECT *p) asm("EnterCritSect__FP8CRITSECT");
void LeaveCritSect(CRITSECT *p) asm("LeaveCritSect__FP8CRITSECT");
void FlushCache(int n) asm("FlushCache");
void sceGsPutDrawEnv(GSDB *p) asm("sceGsPutDrawEnv");
void sceDmaSend(int ch, QW *aqw) asm("sceDmaSend");
void sceDmaSync(int ch, int a, int b) asm("sceDmaSync");
}
void BlastAqwGifsBothFrames(QW *aqw)
{
    EnterCritSect(&D_002DFB40);
    FlushCache(0);
    for (int i = 0; i < 2; i++)
    {
        sceGsPutDrawEnv(((i + D_002DEDB0) & 1) ? &D_002DEBD0 : &D_002DECC0);
        sceDmaSend(g_pdcGif, aqw);
    }
    sceDmaSync(g_pdcGif, 0, 0);
    LeaveCritSect(&D_002DFB40);
}
