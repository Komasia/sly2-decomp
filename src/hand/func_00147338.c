/* OnOverlayMessage: the overlay's message handler: the base handling, then its own animation's events (message 9
 * from its ASEGA): 0x5FB / 0x5FC the overlay may / may not be closed, 0x5FD / 0x5FE skipped, 0x600 / 0x5FF it accepts
 * input or not, and 0x601 waits for its dialog (state 3) when it has one. Layout: SafeHouse port (overlay.cpp). */
/* message 9: an animation's event */
struct ASEGMSG9 {
    /* 0x0 */ void *pasega;   /* the animation sending it */
    /* 0x4 */ int unk4;
    /* 0x8 */ int n;          /* the event */
};
struct OVERLAY {
    /* 0x000 */ char pad[0x160];
    /* 0x160 */ void *pasega;   /* field: SafeHouse port */
    /* 0x164 */ int canClose;   /* field: SafeHouse port */
    /* 0x168 */ int canSkip;    /* field: SafeHouse port */
    /* 0x16c */ int accepts;    /* field: SafeHouse port */
    /* 0x170 */ int dialog;     /* field: SafeHouse port (-1 none) */
};
#define MSGID_AsegEvent 9
#define OVEV_CanClose    0x5FB
#define OVEV_NoClose     0x5FC
#define OVEV_CanSkip     0x5FD
#define OVEV_NoSkip      0x5FE
#define OVEV_NoAccept    0x5FF
#define OVEV_Accept      0x600
#define OVEV_WaitDialog  0x601
void func_00133590(struct OVERLAY *poverlay, int msgid, struct ASEGMSG9 *pmsg);   /* the base message handler */
void func_00147410(struct OVERLAY *poverlay, int state);   /* the overlay's state */
// name: SafeHouse port (OnOverlayMessage)
void OnOverlayMessage__FP2LO5MSGIDPv(struct OVERLAY *poverlay, int msgid, struct ASEGMSG9 *pmsg)
{
    func_00133590(poverlay, msgid, pmsg);
    if (msgid != MSGID_AsegEvent) return;
    if (pmsg->pasega != poverlay->pasega) return;
    switch (pmsg->n) {
    case OVEV_CanClose: poverlay->canClose = 1; break;
    case OVEV_NoClose: poverlay->canClose = 0; break;
    case OVEV_CanSkip: poverlay->canSkip = 1; break;
    case OVEV_NoSkip: poverlay->canSkip = 0; break;
    case OVEV_NoAccept: poverlay->accepts = 0; break;
    case OVEV_Accept: poverlay->accepts = 1; break;
    case OVEV_WaitDialog:
        if (poverlay->dialog != -1) func_00147410(poverlay, 3);
        break;
    }
}
