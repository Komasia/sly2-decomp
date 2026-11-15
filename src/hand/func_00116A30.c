/* Allocates n bytes from the SW heap (kind 0x10) through PvAllocSwImpl; the first argument is unused (a
 * method's this: Sly 3 maps it to CGlobalHeap::PvAlloc). */
typedef struct MSG { int n; int nKind; } MSG;
void PvAllocSwImpl__Fi(MSG *pmsg);

void func_00116A30(void *pv, int n)
{
    MSG msg;
    msg.n = n;
    msg.nKind = 0x10;
    PvAllocSwImpl__Fi(&msg);
}
