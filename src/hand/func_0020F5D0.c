extern int D_003E1C30;
extern int D_003E1C54;
extern int D_003E1C58;
int S32Read(void *pbis) asm("S32Read__18CBinaryInputStream");
// name: SafeHouse port (LoadBulkHeaderFromBrx)
void LoadBulkHeaderFromBrx__FiPv(int a, void *pbis)
{
    int x = S32Read(pbis);
    int y = S32Read(pbis);
    D_003E1C30 = x;
    if (y != D_003E1C58) a = 1;
    D_003E1C54 = a;
    D_003E1C58 = y;
}
