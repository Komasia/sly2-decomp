/* PostBombLoad: the base post-load (0x1F36A8), then a projectile with sweep entries (+0x1F4) gets 0xC0 bytes of sweep
 * state on the world heap (+0x1FC). Layout: SafeHouse port (projectile.cpp: +0x1F8 / +0x1FC the sweep). */
struct AREQ { int cb; int cbAlign; };
struct BOMB { char pad[0x1f4]; int csweep; int asweep; int psweepState; };
void func_001F36A8(struct BOMB *);
int PvAllocSwImpl__Fi(struct AREQ *);
void PostBombLoad__FP4BOMB(struct BOMB *pbomb) {
    func_001F36A8(pbomb);
    if (pbomb->csweep) { struct AREQ areq; areq.cb = 0xc0; areq.cbAlign = 0x10; pbomb->psweepState = PvAllocSwImpl__Fi(&areq); }
}
