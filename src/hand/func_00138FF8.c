/* PblipNew (Sly 1 blip.c, by module order): a new blip of the group from the world's slot heap (+0x4088), with its
 * rolling state (BLIPSP, +0x40A0) when the group's blips roll (BLIPOK 2); appended to the group's list; null when a slot
 * heap is empty. */
struct BLIP { char pad[0x1088]; void *pblipsp; void *pblipg; };   /* Sly 1 blip.h BLIP */
struct BLIPG { char pad[0x160]; int blipok; char pad2[0x448 - 0x164]; int dlBlip; };   /* +0x160: the blips' motion kind (Sly 1 BLIPOK, 2 rolling) */
struct SW { char pad[0x4088]; int slotheapBlip; char pad2[0x40a0 - 0x408c]; int slotheapBlipsp; };
struct BLIP *func_0011CCC0(void *);
void func_0011CD98(void *, struct BLIP *);
void AppendDlEntry__FP2DLPv(void *, struct BLIP *);
struct BLIP *func_00138FF8(struct SW *psw, struct BLIPG *pblipg) {
    void *pslotheap = &psw->slotheapBlip;
    struct BLIP *pblip = func_0011CCC0(pslotheap);
    if (!pblip) return 0;
    if (pblipg->blipok == 2) {
        pblip->pblipsp = func_0011CCC0(&psw->slotheapBlipsp);
        if (!pblip->pblipsp) { func_0011CD98(pslotheap, pblip); return 0; }
    }
    pblip->pblipg = pblipg;
    AppendDlEntry__FP2DLPv(&pblipg->dlBlip, pblip);
    return pblip;
}
