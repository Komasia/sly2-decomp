/* class: OVERLAY (cid 0x68; SafeHouse activate.cpp "0x68: 0x21 | 0x102 (0x1471C0)"), its init: the SO's init, no
 * state (-1), the object's activation state 1 (SetLoSt), and its update flags (+0x40) given GRFUPD_Update |
 * GRFUPD_RealTime, so it is updated on the real clock while the game is paused. The flags word is tagged: with its
 * low bit set it holds the flags, else it points at the update table entry's flags. */
struct OVERLAY {
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ unsigned int grfUpd;   /* the update flags (low bit set) or a pointer to them */
    /* 0x044 */ char pad44[0x150 - 0x44];
    /* 0x150 */ int state;             /* field: SafeHouse port (overlay.cpp OVERLAY) */
};
#define GRFUPD_Flags    0x001   /* SafeHouse update.h: the word holds the flags, not a pointer */
#define GRFUPD_Update   0x002   /* has an update (vt slot 16) */
#define GRFUPD_RealTime 0x100   /* updated on the real clock too */
void InitSo__FP2SO(struct OVERLAY *poverlay);
void func_001A6CA8(struct OVERLAY *poverlay, int st);   /* SafeHouse SetLoSt (option 14) */
void func_001471C0(struct OVERLAY *poverlay)
{
    unsigned int grfUpd;
    InitSo__FP2SO(poverlay);
    poverlay->state = -1;
    func_001A6CA8(poverlay, 1);
    grfUpd = poverlay->grfUpd;
    if ((grfUpd ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grfUpd |= GRFUPD_RealTime | GRFUPD_Update;
    else poverlay->grfUpd = grfUpd | GRFUPD_RealTime | GRFUPD_Update;
}
