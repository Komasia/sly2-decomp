/* class: the screen player (SafeHouse splayer.h StopRoot, orig 0x00218638; see r7_candidates): the root's entry 0
 * stopped when +0x28 is set. */
struct SPLAYER {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int f28;
};
void StopEntrySound__FP8SENTRYRTi(struct SPLAYER *p, int ientry);

void func_00218638(struct SPLAYER *psplayer, int n)
{
    if (psplayer->f28 != 0) {
        StopEntrySound__FP8SENTRYRTi(psplayer, 0);
    }
}
