/* func_0020C290 (0x20C290): the kind-2 player's ASEGA listener: an event message (9) of the launch event 0x22
 * starts the flight (K2ST_Air); then the base handler. */
#include "h6_guard.h"
struct ASEGMSG { int unk_0x00, unk_0x04, nEvent; };
void SetK2State__FP6K2PLAYi(void *pk2play, int st);
int func_00133590(void *pk2play, int msg, struct ASEGMSG *pmsg);
#define MSG_AsegEvent 9
int func_0020C290(void *pk2play, int msg, struct ASEGMSG *pmsg) { if (msg == MSG_AsegEvent && pmsg->nEvent == 0x22) SetK2State__FP6K2PLAYi(pk2play, K2ST_Air); return func_00133590(pk2play, msg, pmsg); }
