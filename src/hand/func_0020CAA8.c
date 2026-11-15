struct ASEGMSG9 { int unk_0x00, unk_0x04, nEvent; };
struct K3PLAY { char pad[0x34]; int fForward; int fBackward; };
#define MSG_AsegEvent 9
void func_00133590(struct K3PLAY *pk3play, int msg, struct ASEGMSG9 *pmsg);
/* OnK3Event (0x20CAA8): the directional player's ASEGA listener: the clip's marker pairs 0x17D / 0x17E and
 * 0x17F / 0x180 open and close the windows in which it may change to another direction (forward / backward); then
 * the base handler. */
// name: SafeHouse port (OnK3Event)
void OnK3Event__FP6K3PLAYiP8ASEGMSG9(struct K3PLAY *pk3play, int msg, struct ASEGMSG9 *pmsg)
{
    if (msg == MSG_AsegEvent) {
        switch (pmsg->nEvent) {
        case 0x17D: pk3play->fForward = 1; break;
        case 0x17E: pk3play->fForward = 0; break;
        case 0x17F: pk3play->fBackward = 1; break;
        case 0x180: pk3play->fBackward = 0; break;
        }
    }
    func_00133590(pk3play, msg, pmsg);
}
