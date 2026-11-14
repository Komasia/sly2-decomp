/* CSndPlain::CSndPlain(int sfxid) (0x1FBBC8; SafeHouse sound.h / sound.cpp): the base constructor (CSnd 0x1FAFD0), the
 * world sound id (+0x60), the vtable 0x2D9C70, then dirty bit 1 set (it starts at once). */
// name: SafeHouse port (CSndPlain::CSndPlain, sound.h "explicit CSndPlain(int sfxid); // 0x1FBBC8")
typedef struct CSndPlain {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x50];
    /* 0x60 */ int m_sfxid;
} CSndPlain;

CSndPlain *__4CSnd(CSndPlain *psnd);
void SetDirty__4CSndUiUi(CSndPlain *psnd, unsigned int grfMask, unsigned int grfValue);
extern char D_002D9C70[];   /* CSndPlain's vtable */

CSndPlain *__9CSndPlaini(CSndPlain *psnd, int sfxid)
{
    __4CSnd(psnd);
    psnd->m_sfxid = sfxid;
    psnd->pvt = D_002D9C70;
    SetDirty__4CSndUiUi(psnd, 1, 1);
    return psnd;
}
