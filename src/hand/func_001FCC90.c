/* class: CSndVoice (vtable 0x2D9BE0): its AddRef (vtable entry 1; SafeHouse sound.h "void AddRef() { ++m_cref; } // slot 1", the
 * Release is 0x1FCCA0). */
typedef struct CSND {
    /* 0x00 */ char pad0[0x4c];
    /* 0x4c */ unsigned short m_cref;   /* field: SafeHouse port */
} CSND;

void func_001FCC90(CSND *psnd)
{
    psnd->m_cref++;
}
