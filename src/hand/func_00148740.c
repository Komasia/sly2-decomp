/* class: a trigger state (SafeHouse trigger.cpp: embedded in pads at +0x150 and volumes at +0x130): its post-load,
 * resolving its two animation lists (0 enter, 1 leave) around its owner. */
struct TRIGASEGLIST { char b[0x44]; };   /* a count and eight entries */
struct TRIGGERSTATE {
    /* 0x00 */ int ploOwner;
    /* 0x04 */ struct TRIGASEGLIST alist[2];
};
void RunTriggerAsegList__FP2LOPv(struct TRIGASEGLIST *plist, int ploOwner);
void func_00148740(struct TRIGGERSTATE *ptrig)
{
    unsigned int i;
    for (i = 0; i < 2; i++) RunTriggerAsegList__FP2LOPv(&ptrig->alist[i], ptrig->ploOwner);
}
