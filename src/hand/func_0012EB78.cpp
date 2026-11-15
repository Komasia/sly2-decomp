// The ambient sound object's (cid 0x2B) load (SafeHouse loaders.cpp LoadLox12EB78FromBrx, soundglue.cpp AMBREC):
// room for 8 sound records (0x14 bytes) and 8 falloff records (0x10 bytes) on the stack while the object loads
// (the EOPID 99 / 100 options append to them: 0x12EEE0 / 0x12EF40), then both lists are copied to the world heap
// at their real sizes.
struct AREQ { int cb; int cbAlign; };
struct OBJ { int a[4]; OBJ(); ~OBJ(); };   // the stack frame scope of the temporary allocations
struct T {
    char pad[0xE4];
    int csnd;          // +0xE4 field: SafeHouse port (AMBREC asnd)
    void *asnd;        // +0xE8
    int pad2;          // +0xEC (the sounds while active)
    int cfall;         // +0xF0 field: SafeHouse port (AMBREC afall)
    void *afall;       // +0xF4
};
extern "C" {
void *PvAllocStackClearImpl(AREQ *preq) asm("PvAllocStackClearImpl__Fi");
void *PvAllocSwCopyImpl(AREQ *preq, void *pv) asm("PvAllocSwCopyImpl__FiPv");
void LoadXfmFromBrx(T *pamb, void *pbis) asm("LoadXfmFromBrx__FP3XFMP18CBinaryInputStream");
void func_0012EB78(T *pamb, void *pbis);
}
void func_0012EB78(T *pamb, void *pbis)
{
    OBJ obj;
    AREQ req;
    AREQ *preq = &req;
    req.cb = 0xA0;
    preq->cbAlign = 0x10;
    pamb->asnd = PvAllocStackClearImpl(preq);
    req.cb = 0x80;
    preq->cbAlign = 0x10;
    pamb->afall = PvAllocStackClearImpl(preq);
    LoadXfmFromBrx(pamb, pbis);
    req.cb = pamb->csnd * 0x14;
    preq->cbAlign = 0x10;
    pamb->asnd = PvAllocSwCopyImpl(preq, pamb->asnd);
    req.cb = pamb->cfall * 0x10;
    preq->cbAlign = 0x10;
    pamb->afall = PvAllocSwCopyImpl(preq, pamb->afall);
}
