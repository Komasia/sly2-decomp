/* CSnd::SetPan: the sound's pan in degrees, wrapped to 0..359; a change marks the pan dirty (0x20).
 * Layout: SafeHouse port (sound.h CSnd). */
struct CSnd {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ int m_pan;   /* field: SafeHouse port */
};
void SetDirty__4CSndUiUi(struct CSnd *psnd, unsigned int grfMask, unsigned int grf);

// name: SafeHouse port (CSnd::SetPan)
void SetPan__4CSndi(struct CSnd *psnd, int deg)
{
    int m = deg % 360;
    int pan = m > -1 ? m : m + 360;
    if (pan != psnd->m_pan) {
        psnd->m_pan = pan;
        SetDirty__4CSndUiUi(psnd, 0x20, 0x20);
    }
}
