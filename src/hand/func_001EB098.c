struct AR { int cb; int cbAlign; };
struct E { int id; unsigned char b4; char pad[0x28 - 5]; };
extern int D_003DCFF0;
extern struct E *D_003DCFF4;
extern int D_003DCF98;
int func_00117C20(void *pbis);
void *PvAllocStackClearImpl__Fi(struct AR *par);
void LoadBmpFromBrx__FP18CBinaryInputStreamP3BMP(void *pbis, struct E *pe);
// name: SafeHouse port (LoadBmpsFromBrx)
void LoadBmpsFromBrx__FP18CBinaryInputStream(void *pbis)
{
    struct AR ar;
    int i = 0;
    D_003DCFF0 = func_00117C20(pbis);
    ar.cb = D_003DCFF0 * sizeof(struct E);
    ar.cbAlign = 0x10;
    D_003DCFF4 = PvAllocStackClearImpl__Fi(&ar);
    D_003DCF98 = 0;
    for (; i < D_003DCFF0; i++) {
        LoadBmpFromBrx__FP18CBinaryInputStreamP3BMP(pbis, &D_003DCFF4[i]);
        if (D_003DCFF4[i].b4 == 1) D_003DCF98++;
    }
    if (D_003DCF98 < D_003DCFF0 - D_003DCF98) D_003DCF98 = D_003DCFF0 - D_003DCF98;
}
