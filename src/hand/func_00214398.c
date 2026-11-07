struct S { char pad[0xC4]; void *xC4; };
extern int D_002C40A4;
int func_00117C20(void *a);
int PvAllocClear__FP4HEAPii(void *heap, int cb, int k);
void LoadElemFromBrx__FP5OWNERP18CBinaryInputStreamP4ROOTiP6SPRITE(struct S *p, void *a, void *b, int n, int m);
// name: SafeHouse port (LoadElemsFromBrx)
void LoadElemsFromBrx__FPvP18CBinaryInputStreamT0PiT3(struct S *p, void *a, void *b, int *pn, int *pm)
{
    int i;
    *pn = func_00117C20(a);
    *pm = PvAllocClear__FP4HEAPii(p->xC4, (*pn + 1) << 6, D_002C40A4 ? 0x13 : 0x11);
    for (i = 1; i <= *pn; i++)
        LoadElemFromBrx__FP5OWNERP18CBinaryInputStreamP4ROOTiP6SPRITE(p, a, b, *pn, *pm);
}
