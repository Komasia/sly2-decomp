/* LoadBulkHeaderFromBrx (0x20F5D0): the bulk records' header: their size and their checksum; they are loaded (again)
 * when forced or when the checksum changed. */
extern int D_003E1C30;   /* the bulk records' size */
extern int D_003E1C54;   /* whether to load them */
extern int D_003E1C58;   /* the loaded ones' checksum */
int S32Read(void *pbis) asm("S32Read__18CBinaryInputStream");
// name: SafeHouse port (LoadBulkHeaderFromBrx)
void LoadBulkHeaderFromBrx__FiPv(int fForce, void *pbis)
{
    int cb = S32Read(pbis);
    int nChecksum = S32Read(pbis);
    D_003E1C30 = cb;
    if (nChecksum != D_003E1C58) fForce = 1;
    D_003E1C54 = fForce;
    D_003E1C58 = nChecksum;
}
