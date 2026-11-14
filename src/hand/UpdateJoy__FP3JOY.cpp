struct JOY {
    char pad0[0x1000];
    int nPort;      /* 0x1000 */
    int nSlot;      /* 0x1004 */
    int x1008;
    int joys;       /* 0x100C */
    int joyk;       /* 0x1010 */
    float tJoys;    /* 0x1014 */
    char pad1018[0x10CC - 0x1018];
    char rumble[0x10E8 - 0x10CC]; /* 0x10CC */
    int fRumbleEnabled; /* 0x10E8 */
};

#include "clock.h"

extern "C" {
int scePadGetState(int port, int slot) asm("scePadGetState");
int scePadInfoMode(int port, int slot, int term, int offs) asm("scePadInfoMode");
int scePadSetMainMode(int port, int slot, int offs, int lock) asm("scePadSetMainMode");
int scePadInfoAct(int port, int slot, int term, int offs) asm("scePadInfoAct");
void *s1_memset(void *pv, int b, int cb) asm("memset");
int scePadSetActAlign(int port, int slot, unsigned char *pb) asm("scePadSetActAlign");
int scePadInfoPressMode(int port, int slot) asm("scePadInfoPressMode");
int scePadEnterPressMode(int port, int slot) asm("scePadEnterPressMode");
int scePadGetReqState(int port, int slot) asm("scePadGetReqState");
int FReadJoy(JOY *pjoy) asm("FReadJoy__FP3JOY");
void UpdateRumble(void *prumble) asm("UpdateRumble__FP6RUMBLE");
void SetJoyJoys(JOY *pjoy, int joys, int joyk) asm("SetJoyJoys__FP3JOY4JOYS4JOYK");
}

void UpdateJoy(JOY *pjoy)
{

    int fReady;
    int x;
    int joys, joyk;
    int state;



    fReady = 0;

    if (pjoy->joys == 0)
        return;

    state = scePadGetState(pjoy->nPort, pjoy->nSlot);
    if (state == 6 || state == 2)

        fReady = 1;


    if (pjoy->joys != 3 && pjoy->joyk != 0) {
        if (g_clock.tReal - pjoy->tJoys >= 2.0f)
            state = 0;
    }

    if (pjoy->joyk != 0 && state == 0)
        SetJoyJoys(pjoy, 1, 0);


    if (!fReady)
        return;

    x = 2;

    joys = pjoy->joys;
    joyk = pjoy->joyk;

    switch (joys) {
    case 1:
        switch (joyk) {
        case 0: {

            int m;
            int n = scePadInfoMode(pjoy->nPort, pjoy->nSlot, 1, 0);
            if (n == 0)
                break;
            m = scePadInfoMode(pjoy->nPort, pjoy->nSlot, 2, 0);
            if (m > 0)
                n = m;
            if (n == 4 || n == 7) {

                joyk = 1;
                joys = m ? 1 : 3;
            }
            break;
        }
        case 1:

            if (scePadSetMainMode(pjoy->nPort, pjoy->nSlot, 1, 3) == 1)
                joys = 2;

            break;
        case 2: {
            unsigned char ab[6];
            int i;

            x = scePadInfoAct(pjoy->nPort, pjoy->nSlot, -1, 0);
            if (x != 2 ||

                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 0, 1) != 1 ||
                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 0, 2) != 2 ||
                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 0, 3) != 0 ||
                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 1, 1) != 1 ||
                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 1, 2) != 1 ||
                scePadInfoAct(pjoy->nPort, pjoy->nSlot, 1, 3) != 1) {
                joys = 3;
                break;
            }
            s1_memset(ab, 0xFF, 6);
            for (i = 0; i < x; i++)
                ab[i] = i;
            if (scePadSetActAlign(pjoy->nPort, pjoy->nSlot, ab) == 1)
                joys = 2;
            break;
#undef x
        }
        case 3:
            if (scePadInfoPressMode(pjoy->nPort, pjoy->nSlot) != 1) {
                joys = 3;
                break;
            }
            if (scePadEnterPressMode(pjoy->nPort, pjoy->nSlot) == 1)
                joys = x;
            break;
        }
        break;
    case 2:
        switch (scePadGetReqState(pjoy->nPort, pjoy->nSlot)) {
        case 1:
            joys = 1;
            break;
        case 2:
            break;
        case 0:
            switch (pjoy->joyk) {
            case 1:
                joyk = 2;
                joys = 1;
                break;
            case 2:
                joyk = 3;
                joys = 1;
                break;
            case 3:
                joyk = 4;
                joys = 3;
                break;
            default:
                joyk = 0;
                break;
            }
            break;
        default:
            joyk = 0;
            break;
        }
        break;
    case 3:
        if (FReadJoy(pjoy)) {
            if (pjoy->fRumbleEnabled && pjoy->joyk >= 3)
                UpdateRumble(pjoy->rumble);
        } else {
            joys = 1;
            joyk = 0;
        }
        break;
    }

    SetJoyJoys(pjoy, joys, joyk);
}
