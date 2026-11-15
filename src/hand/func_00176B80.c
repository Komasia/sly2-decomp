struct CTMSG { int psource; int pvOther; int preceiver; int grfKind; int n; int pad2[0x13]; };   /* the contact message (SafeHouse ai.h HIT) */
struct JOBREACT { char pad[0x10]; int pguard; };
void *s1_memset(void *pv, int b, int cb) asm("memset");
void PaloAcceptContact__FP5CTMSG(struct CTMSG *pctmsg);
/* JOBREACT::SendHit: send a contact message to the guard: kind 0x40000 from plo, with the amount n. */
// name: SafeHouse port (JOBREACT::SendHit)
void SendHit__8JOBREACTii(struct JOBREACT *pjob, int n, int plo) { struct CTMSG ctmsg; s1_memset(&ctmsg, 0, sizeof(ctmsg)); ctmsg.psource = plo; ctmsg.n = n; ctmsg.grfKind = 0x40000; ctmsg.preceiver = pjob->pguard; PaloAcceptContact__FP5CTMSG(&ctmsg); }
