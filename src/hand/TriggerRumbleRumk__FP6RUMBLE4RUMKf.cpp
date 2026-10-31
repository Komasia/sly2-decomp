struct RUMBLE;
struct RUMPAT { char ab[0x104]; };
enum RUMK { RUMK_Nil = -1 };
extern RUMPAT s_mprumkrumpat[];
void TriggerRumbleRumpat(RUMBLE *prumble, RUMPAT *prumpat, float dt);
void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt)
{
    TriggerRumbleRumpat(prumble, &s_mprumkrumpat[rumk], dt);
}
