typedef struct CHK { int a[0x4C / 4]; } CHK;
typedef struct CHKMGR { char pad[0x3BF0]; int fRestored; CHK chk; } CHKMGR;
void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr, CHK *pchk) __asm__("RestoreChkmgrFromCheckpoint__FP6CHKMGR");
void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr, CHK *pchk)
{
    pchkmgr->fRestored = 1;
    pchkmgr->chk = *pchk;
}
