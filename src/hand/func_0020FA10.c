/* func_0020FA10 (0x20FA10): the usual collision-entry filter: not a sensor entry (bit 48), not of an attachment
 * marked 4, and not of the context attachment (the asking object's own). */
struct OXA { char pad[0x70]; long grf; };
struct ALOX { char pad[0xEC]; struct OXA *poxa; };
struct SOE { int unk_0x00; struct ALOX *palo; char pad[8]; long grf; };
int func_0020FA10(struct OXA *poxaOwn, struct SOE *psoe) {
    int fKeep = 0;
    if (!(psoe->grf & 0x1000000000000L)) {
        struct OXA *poxa = psoe->palo->poxa;
        if (!(poxa->grf & 4)) fKeep = poxa != poxaOwn;
    }
    return fKeep;
}
