#include "cid.h"
class OBase { public: int a, b, c; virtual void V1(); virtual void V2(); virtual void V3(); virtual void V4(); virtual void V5();
 virtual void V6(); virtual void V7(); virtual void V8(); virtual void V9(); };
class FADE : public OBase { public: char pad[0x54 - 0x10]; unsigned int grf54; char p2[8]; float g60; float g64; int p68; int n6C; };   /* cid 0x74; vt slot 9: its post-load */
struct SW { char pad[0x3E60]; FADE *pfade; };
extern "C" FADE *PloNew(int cid, void *psw, int oid, int n) asm("PloNew__F3CIDP2SW3OIDi");
// func_0020E338 (0x20E338): the world's fade object (cid 0x74, no oid; SafeHouse update.h g_ploFadeRecover: the fade
// after a fall's recovery): 0.1 / 0.25, flags 0x80200000, +0x6C 1, then its post-load (vt slot 9).
extern "C" void func_0020E338(SW *psw)
{
    psw->pfade = PloNew(CID_FADE, 0, -1, -1);
    psw->pfade->g60 = 0.1f;
    psw->pfade->g64 = 0.25f;
    psw->pfade->grf54 = 0x80200000;
    psw->pfade->n6C = 1;
    psw->pfade->V9();
}
