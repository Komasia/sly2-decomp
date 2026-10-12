struct RUMINS { char pad[4]; unsigned char fHighSpeedMotor; unsigned char bLowSpeedMotor; };
struct RUMPAT { RUMINS arumins[1]; };
enum RUMS { RUMS_Dead, RUMS_Idle, RUMS_Rumble, RUMS_Stop, RUMS_Kill };
struct RUMBLE { int nPort; int nSlot; RUMS rums; RUMPAT *prumpat; int pad; int pad2; float dtRumins; };
struct CLOCK { float t; float dt; float a[6]; float dtReal; };
extern CLOCK D_002DDED0;
extern "C" int func_00243870(int, int, unsigned char *);
void StopRumbleActuators(RUMBLE *prumble);
void SetRumbleRums(RUMBLE *prumble, RUMS rums)
{
    if (rums == prumble->rums)
        return;
    unsigned char abShockDirect[6];
    switch (rums)
    {
    case RUMS_Dead:
    case RUMS_Idle:
        break;
    case RUMS_Rumble:
        abShockDirect[0] = prumble->prumpat->arumins[0].fHighSpeedMotor;
        abShockDirect[1] = prumble->prumpat->arumins[0].bLowSpeedMotor;
        func_00243870(prumble->nPort, prumble->nSlot, abShockDirect);
        prumble->rums = rums;
        break;
    case RUMS_Stop:
    case RUMS_Kill:
        StopRumbleActuators(prumble);
        prumble->dtRumins = D_002DDED0.a[0] * 4.0f;
    default:
        prumble->rums = rums;
        break;
    }
}
