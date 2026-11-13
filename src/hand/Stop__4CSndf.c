/* CSnd::Stop: stop a sound, fading out over tFade seconds (+0x48): marks the sound dirty (SetDirty(0x1FFF, 8)). */
struct CSnd {
    /* 0x00 */ char pad0[0x48];
    /* 0x48 */ float m_tFade;   /* field: SafeHouse port */
};
void SetDirty(struct CSnd *psnd, unsigned int grf, unsigned int grfAdd) asm("SetDirty__4CSndUiUi");

// name: SafeHouse port (CSnd::Stop)
void Stop__4CSndf(struct CSnd *psnd, float tFade)
{
    psnd->m_tFade = tFade;
    SetDirty(psnd, 0x1FFF, 8);
}
