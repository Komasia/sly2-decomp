struct RUMBLE { int nPort; int nSlot; };
extern "C" int func_00243870(int, int, unsigned char *);
void StopRumbleActuators(RUMBLE *prumble)
{
    unsigned char abShockDirect[6];
    abShockDirect[0] = 0;
    abShockDirect[1] = 0;
    func_00243870(prumble->nPort, prumble->nSlot, abShockDirect);
}
