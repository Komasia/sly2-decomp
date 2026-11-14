/* class: the suck meter D_002DE578 (GSuck 0x154C90 reads its +0x8 / +0xC / +0x10 progress records): cleared
 * (0x18 bytes; called by 0x1613F8 when a game is reset). */
typedef struct SUCK {
    /* 0x00 */ int an[2];
    /* 0x08 */ void *apv[3];   /* the three progress records */
    /* 0x14 */ int n14;
} SUCK;

void *memset(void *pv, int b, unsigned int cb);

void func_00154A60(SUCK *psuck)
{
    memset(psuck, 0, sizeof(SUCK));
}
