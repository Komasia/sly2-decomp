/* the reaction job (0x9C): its state */
struct JOBREACT { char pad[0x30]; int st; };
/* an AI message: its kind */
struct AIMSG { int k; int an[27]; };
struct GUARD { char pad[0x26C]; char bhvstk[0x2DC - 0x26C]; int saved2DC[3]; int pcmdlistPatrol; };
void *s1_memset(void *pv, int c, int cb) asm("memset");
struct JOBREACT *PjobFind__FP5GUARDPv(void *pbhvstk, int cid);
void React__8JOBREACTP5AIMSG(struct JOBREACT *pjobreact, struct AIMSG *pmsg);
/* SetGuardPatrol (0x20A540): gives the guard a new patrol command list (its saved script place cleared); a reaction
 * job in state 1 is restarted on it (reacts to -1, then to 1 again). */
// name: SafeHouse port (SetGuardPatrol)
void SetGuardPatrol__FP5GUARDi(struct GUARD *pguard, int pcmdlist)
{
    if (pguard->pcmdlistPatrol != pcmdlist) {
        struct JOBREACT *pjobreact;
        pguard->pcmdlistPatrol = pcmdlist;
        s1_memset(pguard->saved2DC, 0, 0xC);
        pjobreact = PjobFind__FP5GUARDPv(pguard->bhvstk, 0x9C);
        if (pjobreact) {
            int st = pjobreact->st;
            if (st == 1) {
                struct AIMSG msg;
                s1_memset(&msg, 0, sizeof(msg));
                msg.k = -1;
                React__8JOBREACTP5AIMSG(pjobreact, &msg);
                s1_memset(pguard->saved2DC, 0, 0xC);
                msg.k = st;
                React__8JOBREACTP5AIMSG(pjobreact, &msg);
            }
        }
    }
}
