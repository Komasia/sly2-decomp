#include "vtbl.h"
struct LOV { char pad[0xC]; VTENT *pvt; };
/* the world fields used here: the two 12-byte record arrays (sw.h), the objects of the load, four slot heaps, the
 * collision meshes */
struct SW {
    char pad0[0x39D0]; int aUnk39d0; int pad39D4; int aUnk39d8; int pad39DC; struct LOV **pploLoadFirst; struct LOV **pploLoadLast;
    char pad1[0x403C - 0x39E8]; char aslotheap403C[0x18]; char aslotheap4054[0x1C]; char aslotheap4070[0x18]; char aslotheap4088[4];
    char pad2[0x45CC - 0x408C]; void *pmeshes45CC;
};
extern char g_cm[], g_game[], D_003D9E70[];
void func_0011CDD8(void *pslotheap);
void func_0020E338(struct SW *psw);
void func_0020E2B0(struct SW *psw);
void ShutdownSwSplice__FP2SW(struct SW *psw);
void func_001CA500(struct SW *psw);
void func_0020F710(struct SW *psw);
void func_001569B8(struct SW *psw);
void func_001A3260(struct SW *psw);
void InitSwNav__FP2SW(struct SW *psw);
void func_00210940(struct SW *psw);
void func_001957C0(struct SW *psw);
void InitHudWidgets(void *psw) asm("InitHudWidgets__FP2SW");
void RunDeferredSpliceEvents__FP2SW(struct SW *psw);
void func_001C1260(void *pmeshes);
void StartupCm(void *pcm) asm("StartupCm__Fv");
void BroadcastTaskEvent__FP2SWiP2LO(void *psw, int nEvent, int plo);

/* StartSw (0x20E740): the world's start after a load: its slot heaps reset (0x11CDD8), the fade object and the
 * light (0x20E338 / 0x20E2B0), the splice shutdown, the spare instances, the counters, the noises, the nav, the HUD
 * widgets; then the loaded objects' post-loads (vt slot 15) with the deferred splice events until none are left;
 * the meshes (0x1C1260), the camera, and task event 4. */
// name: SafeHouse port (StartSw)
void StartSw__FP2SW(struct SW *psw)
{
    struct LOV **pplo;
    func_0011CDD8(psw->aslotheap403C);
    func_0011CDD8(psw->aslotheap4054);
    func_0011CDD8(psw->aslotheap4070);
    func_0011CDD8(psw->aslotheap4088);
    func_0020E338(psw);
    func_0020E2B0(psw);
    ShutdownSwSplice__FP2SW(psw);
    func_001CA500(psw);
    func_0020F710(psw);
    func_001569B8(psw);
    func_001A3260(psw);
    InitSwNav__FP2SW(psw);
    func_00210940(psw);
    func_001957C0(psw);
    InitHudWidgets(D_003D9E70);
    while (RunDeferredSpliceEvents__FP2SW(psw), psw->pploLoadLast != psw->pploLoadFirst) {
        for (pplo = psw->pploLoadFirst; pplo < psw->pploLoadLast; pplo++)
            ((void (*)(void *))(*pplo)->pvt[15].pfn)(VT_THIS(*pplo, &(*pplo)->pvt[15]));
        psw->pploLoadLast = psw->pploLoadFirst;
    }
    psw->pploLoadLast = 0;
    psw->pploLoadFirst = 0;
    psw->aUnk39d8 = 0;
    psw->aUnk39d0 = 0;
    func_001C1260(psw->pmeshes45CC);
    StartupCm(g_cm);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 4, 0);
}
