// EnsureSggAlarm (0x1E0020): adds an alarm to the relay's alarm list unless it is there already (at most 8).
// The function's name (Sly 1's SGG / ALARM) is kept for its mangled symbol; the object is a relay (relay.h RELAY:
// calarm +0x84, aoidAlarm +0x88) and the "ALARM *" is really the alarm's oid (SafeHouse scpt.cpp: EnsureAlarm).
struct ALARM;
struct SGG { char pad[0x84]; int calarm; ALARM *apalarm[8]; };   // = RELAY's calarm / aoidAlarm
void EnsureSggAlarm(SGG *psgg, ALARM *palarm)
{
    int i;
    for (i = 0; i < psgg->calarm; i++) {
        if (psgg->apalarm[i] == palarm) return;
    }
    if ((unsigned int)psgg->calarm < 8) psgg->apalarm[psgg->calarm++] = palarm;
}
