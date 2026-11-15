/* UpdateSwAaox: when the sweep lists are dirty, an insertion sort of each of the three (by the entries' coordinate):
 * an entry passing an entry of the other kind (a min past a max or back) updates that pair's overlap (UpdateSwPox, k 0).
 * Layout: SafeHouse port (so.h AOX / PHYSW, bbmark.cpp). */
struct OXA;
struct AOX { int fMax; struct OXA *poxa; float *pg; };   /* field: SafeHouse port */
struct SW { char pad[0x3CCC]; int fAaoxDirty; int caox; struct AOX *aaox[3]; };   /* field: SafeHouse port (PHYSW) */
void UpdateSwPox__FP2SWP3OXAT1Uc(struct SW *, struct OXA *, struct OXA *, int);
void *s1_memmove(void *, void *, unsigned int) asm("memmove");
// name: SafeHouse port (UpdateSwAaox)
void UpdateSwAaox__FP2SW(struct SW *psw)
{
    int i;
    if (!psw->fAaoxDirty)
        return;
    psw->fAaoxDirty = 0;
    if (!psw->caox)
        return;
    for (i = 0; i < 3; i++) {
        struct AOX *paox = psw->aaox[i];
        struct AOX *aaox = paox;
        float gMax = *paox->pg;
        int j;
        for (j = psw->caox, paox++; --j > 0; paox++) {
            float g = *paox->pg;
            if (gMax <= g) {
                gMax = g;
            } else {
                struct AOX *paoxIns;
                struct AOX aox;
                for (paoxIns = paox - 1; paoxIns >= aaox; paoxIns--) {
                    if (*paoxIns->pg <= g)
                        break;
                    if (paox->fMax != paoxIns->fMax)
                        UpdateSwPox__FP2SWP3OXAT1Uc(psw, paox->poxa, paoxIns->poxa, 0);
                }
                paoxIns++;
                aox = *paox;
                s1_memmove(paoxIns + 1, paoxIns, (paox - paoxIns) * sizeof(struct AOX));
                *paoxIns = aox;
            }
        }
    }
}
