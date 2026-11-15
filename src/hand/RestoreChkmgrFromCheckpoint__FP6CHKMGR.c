/* RestoreChkmgrFromCheckpoint (0x20E000): a world change requested (SW +0x3BF0 pending) with the given request
 * (+0x3BF4: its flags, the 64-byte checkpoint record, the point and key oids; SafeHouse transition.h TRANSREQ). */
typedef struct TRANSREQ { int a[0x4C / 4]; } TRANSREQ;
typedef struct CHKMGR { char pad[0x3BF0]; int fPending; TRANSREQ req; } CHKMGR;
void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr, TRANSREQ *preq) __asm__("RestoreChkmgrFromCheckpoint__FP6CHKMGR");
void RestoreChkmgrFromCheckpoint(CHKMGR *pchkmgr, TRANSREQ *preq)
{
    pchkmgr->fPending = 1;
    pchkmgr->req = *preq;
}
