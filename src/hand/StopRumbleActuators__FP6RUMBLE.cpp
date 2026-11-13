struct RUMBLE { int nPort; int nSlot; };
extern "C" int scePadSetActDirect(int, int, unsigned char *) asm("scePadSetActDirect");
void StopRumbleActuators(RUMBLE *prumble)
{
    unsigned char abShockDirect[6];
    abShockDirect[0] = 0;
    abShockDirect[1] = 0;
    scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
}
