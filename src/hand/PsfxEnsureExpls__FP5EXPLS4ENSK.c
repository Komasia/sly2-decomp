/* PsfxEnsureExpls: an explosion's sound record (+0xF0), made on first use (0x1FAF70). Layout: SafeHouse port
 * (emitter.cpp). */
struct SFX;
struct EXPLS {
    /* 0x00 */ char pad0[0xf0];
    /* 0xf0 */ struct SFX *psfx;   /* field: SafeHouse port - the sound record */
};
struct SFX *func_001FAF70(void);

struct SFX *PsfxEnsureExpls__FP5EXPLS4ENSK(struct EXPLS *pexpls)
{
    if (!pexpls->psfx)
        pexpls->psfx = func_001FAF70();
    return pexpls->psfx;
}
