/* FUN_0018d2e8 (0x1AC420): writes a save slot's data (0x5408 bytes) to its file on the card. */
struct FILENAME { int a[20]; };
void func_001ABB10(void *pmc, void *pslot, struct FILENAME *pname);
void func_001AC900(void *pmc, struct FILENAME *pname, void *pv, int cb);
#define CB_SAVE 0x5408
void FUN_0018d2e8(void *pmc, void *pslot)
{
    struct FILENAME name;
    func_001ABB10(pmc, pslot, &name);
    func_001AC900(pmc, &name, pslot, CB_SAVE);
}
