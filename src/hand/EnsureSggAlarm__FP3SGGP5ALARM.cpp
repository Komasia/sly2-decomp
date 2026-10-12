struct ALARM;
struct SGG { char pad[0x84]; int calarm; ALARM *apalarm[8]; };
void EnsureSggAlarm(SGG *psgg, ALARM *palarm)
{
    int i;
    for (i = 0; i < psgg->calarm; i++) {
        if (psgg->apalarm[i] == palarm) return;
    }
    if ((unsigned int)psgg->calarm < 8) psgg->apalarm[psgg->calarm++] = palarm;
}
