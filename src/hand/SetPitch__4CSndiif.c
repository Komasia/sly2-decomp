/* CSnd::SetPitch: change a sound's pitch (+0x18) and mark it dirty (0x40). */
struct CSnd {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ float m_pitch;   /* field: SafeHouse port */
};
void SetDirty(struct CSnd *psnd, unsigned int grf, unsigned int grfAdd) asm("SetDirty__4CSndUiUi");

// name: SafeHouse port (CSnd::SetPitch)
void SetPitch__4CSndiif(struct CSnd *psnd, int a, int b, float pitch)
{
    if (pitch != psnd->m_pitch) {
        psnd->m_pitch = pitch;
        SetDirty(psnd, 0x40, 0x40);
    }
}
