/* UpdateBentleyState2: the second state machine (the binocucom's dart: 0 ready, 1 reloading, -1 the binocucom
 * closed, 0x1443D8) until it settles: R1 fires a dart (0x1357C0, contact kind 0x80000), a reload ends after D_002BC994 s; with the binocucom closed, the
 * sub-object's swing mode follows the state (0 stand, 1 moving / jump / interact, 2 near a target), and the log idle
 * (+0x181C) puts the idle machine in state 0x17B. Layout: SafeHouse port (gang.h BENTLEY). */
#include "clock.h"
struct BENTLEY { char pad[0x150]; void *ppadctl; char pad0[0xF20 - 0x154]; int nBinocF20; char pad1[0x1028 - 0xF24]; void *psmIdle; int pad2[2];
    void *psma1034; char pad3[0x13D0 - 0x1038]; int state; char pad4[0x16BC - 0x13D4]; int n16BC; char pad5[0x1700 - 0x16C0];
    float tDart; int pad6[3]; char sub[4]; int nSubState; char pad7[0x181C - 0x1718]; int f181C; };
extern float D_002BC994;   /* the dart reload time */
int func_001443D8(struct BENTLEY *pbentley);
void SetBentleyState2__FP7BENTLEYi(struct BENTLEY *pbentley, int n);
int GrfPadctlTakePressed__FP6PADCTL(void *pv, int n, float g);
void func_001357C0(struct BENTLEY *pbentley, int n);
void UpdateBentleySub__FP7BENTLEYi(void *pv, int n);
int IsmsFindSmOptional(void *pv, int n) asm("IsmsFindSmOptional__FP2SM3OID");
void SetSmaState__FP3SMA3OID(void *pv, int n);
// name: SafeHouse port (UpdateBentleyState2)
void UpdateBentleyState2__FP7BENTLEY(struct BENTLEY *pbentley)
{
    int n16BCOld;
    do {
        n16BCOld = pbentley->n16BC;
        switch (n16BCOld) {
        case 0:
        case 1:
            if (!func_001443D8(pbentley)) {
                SetBentleyState2__FP7BENTLEYi(pbentley, -1);
            } else if (pbentley->n16BC == 1) {
                if (D_002BC994 < g_clock.t - pbentley->tDart)
                    SetBentleyState2__FP7BENTLEYi(pbentley, 0);
            } else if (GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, 8 /* R1 */, 0.25f)) {
                func_001357C0(pbentley, 0x80000);
            }
            break;
        case -1:
            if (func_001443D8(pbentley) && pbentley->nBinocF20 != 2) {
                if (D_002BC994 < g_clock.t - pbentley->tDart)
                    SetBentleyState2__FP7BENTLEYi(pbentley, 0);
                else
                    SetBentleyState2__FP7BENTLEYi(pbentley, 1);
            }
            switch (pbentley->state) {
            case 0:
                UpdateBentleySub__FP7BENTLEYi(pbentley->sub, 0);
                if (pbentley->f181C && pbentley->nSubState != -1 && pbentley->psma1034 && IsmsFindSmOptional(pbentley->psmIdle, 0x17B) >= 0)
                    SetSmaState__FP3SMA3OID(pbentley->psma1034, 0x17B);
                break;
            case 1: case 2: case 3: case 7:
                UpdateBentleySub__FP7BENTLEYi(pbentley->sub, 1);
                break;
            case 5:
                UpdateBentleySub__FP7BENTLEYi(pbentley->sub, 2);
                break;
            default:
                UpdateBentleySub__FP7BENTLEYi(pbentley->sub, -1);
                break;
            }
            break;
        }
    } while (n16BCOld != pbentley->n16BC);
}
