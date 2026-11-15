/* func_001AD480 (0x1AD480): a save slot chosen on the menu page (its index +0x8) for a new game: it becomes the
 * chosen slot (MC +0xFD58); an empty one (no time played, progress key D_003E0FAC) is saved at once
 * (SaveToTarget), else the memory card prompt asks to overwrite (message 0x1C); the page is marked (+0x1C bit 1). */
struct CRef { int m_tagk; float m_tag; };
struct B { char data[0x5464]; };
struct G { char pad[0x24]; struct B aslot[3]; char pad2[0xFD58 - 0x24 - 3 * 0x5464]; struct B *pslotChosen; };  /* MC (include/h5_mc.h) */
struct H { char pad[0x4C]; int x4C; };
struct S { int x0, x4, islot; char pad[0x10]; int grf; };  /* the menu page */
extern struct G D_002E65E0;
extern struct H D_002E6550;
extern int g_keyTimePlayed __asm__("D_003E0FAC");
void NProgress(struct CRef *ret, int a, void *b);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_001ACB58(struct H *h, int n);
void SaveToTarget__Fv(void);
void func_001AD480(struct S *ppage)
{
    struct CRef ref;
    struct B *pslot = &D_002E65E0.aslot[ppage->islot];
    float tPlayed;
    NProgress(&ref, g_keyTimePlayed, pslot);
    tPlayed = ref.m_tag;
    Decref(&ref);
    D_002E65E0.pslotChosen = pslot;
    if (tPlayed == 0.0f)
        SaveToTarget__Fv();
    else
        func_001ACB58(&D_002E6550, 0x1C);
    if (ppage)
        ppage->grf |= 2;
}
