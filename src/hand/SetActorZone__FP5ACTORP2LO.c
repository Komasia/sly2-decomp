/* SetActorZone: the current player's camera zone (+0x1024): the old one's forcing off, the new one's on
 * (SetZoneForced). Other actors are ignored. Source: SafeHouse port (interact.cpp). */
struct LO;
struct ACTOR {
    /* 0x0000 */ char pad0[0x1024];
    /* 0x1024 */ struct LO *plo1024;   /* field: SafeHouse port - the camera zone */
};
extern char g_sw[];
struct ACTOR *PloPlayerPo__FP2SW(void *psw);
void SetZoneForced__FP2LOi(struct LO *plo, int fForced);

// name: SafeHouse port (SetActorZone)
void SetActorZone__FP5ACTORP2LO(struct ACTOR *pactor, struct LO *plo)
{
    struct ACTOR *pactorPlayer = PloPlayerPo__FP2SW(g_sw);
    if (pactorPlayer == pactor) {
        if (pactorPlayer->plo1024 != 0)
            SetZoneForced__FP2LOi(pactorPlayer->plo1024, 0);
        pactorPlayer->plo1024 = plo;
        if (plo != 0)
            SetZoneForced__FP2LOi(plo, 1);
    }
}
