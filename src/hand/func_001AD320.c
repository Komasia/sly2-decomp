/* func_001AD320 (0x1AD320): a save slot chosen on the menu page (its index +0x8) to play: it becomes the game slot;
 * empty (no time played) it is reset first and a new game starts, else its game starts and the page is marked
 * (+0x1C bit 1). */
struct CRef { int m_tagk; float m_tag; };
struct B { char data[0x5464]; };
struct G { char pad[0x24]; struct B aslot[3]; char pad2[0xFD50 - 0x24 - 3 * 0x5464]; struct B *pslotGame; int pslotNewest; struct B *pslotChosen; };  /* MC (include/h5_mc.h) */
struct S { int x0, x4, islot; char pad[0x10]; int grf; };  /* the menu page */
extern struct G D_002E65E0;
extern int g_keyTimePlayed __asm__("D_003E0FAC");
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
void ResetSlotKeepSettings__FPci(struct B *b, int n);
void StartGameFromSave__FP2SW(struct B *b);
void func_001AD320(struct S *ppage)
{
    struct CRef ref;
    struct B *pslot = &D_002E65E0.aslot[ppage->islot];
    float tPlayed;
    NProgress(&ref, g_keyTimePlayed, pslot);
    tPlayed = ref.m_tag;
    Decref(&ref);
    D_002E65E0.pslotGame = pslot;
    if (tPlayed == 0.0f) {
        ResetSlotKeepSettings__FPci(pslot, 1);
        StartGameFromSave__FP2SW(D_002E65E0.pslotGame);
    } else {
        StartGameFromSave__FP2SW(pslot);
        if (ppage)
            ppage->grf |= 2;
    }
}
