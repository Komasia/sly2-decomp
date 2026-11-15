/* HandleStepguardMessage (0x2075D0): GUARD message handler: the PO's, then messages 4 / 5 about this guard and an
 * actor start / stop ground watcher B on that actor (4 only when it is watchable), then the job stack gets the
 * message. */
struct ACTOR { char pad[0x184]; int fWatched; };
struct WATCHB { char pad[0xC]; struct ACTOR *pactor; };
/* the message argument of messages 4 / 5: an actor and the guard it is about */
struct MSGPAIR { struct ACTOR *pactor; void *pguard; };
struct GUARD { char pad[0x26C]; char bhvstk[0x49C - 0x26C]; struct WATCHB *pwatchB; };
void HandlePoMessage__FP2PO5MSGIDPv(struct GUARD *pguard, int msg, struct MSGPAIR *pmsg);
void func_0020D460(struct WATCHB *pwatchB, struct ACTOR *pactor);   /* sets what watcher B watches */
void OfferJobMessage__FP5GUARDii(void *pbhvstk, int msg, struct MSGPAIR *pmsg);
void HandleStepguardMessage__FP9STEPGUARD5MSGIDPv(struct GUARD *pguard, int msg, struct MSGPAIR *pmsg)
{
    HandlePoMessage__FP2PO5MSGIDPv(pguard, msg, pmsg);
    switch (msg) {
    case 4:
        if (pmsg->pguard == pguard && pmsg->pactor->fWatched)
            func_0020D460(pguard->pwatchB, pmsg->pactor);
        break;
    case 5:
        if (pmsg->pguard == pguard && pmsg->pactor == pguard->pwatchB->pactor)
            func_0020D460(pguard->pwatchB, 0);
        break;
    }
    OfferJobMessage__FP5GUARDii(pguard->bhvstk, msg, pmsg);
}
