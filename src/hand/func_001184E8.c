/* class: a CBinaryInputStream over one memory block (vtable 0x2CA5A0; see 0x118480): its Fill (vtable slot 1) -
 * the block becomes the stream's next raw data (m_pbRaw / m_cbRaw), once. */
typedef struct BISMEM {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void *pbRaw;      /* CBinaryInputStream::m_pbRaw */
    /* 0x14 */ int cbRaw;        /* CBinaryInputStream::m_cbRaw */
    /* 0x18 */ char pad18[0x1c];
    /* 0x34 */ int cbBlock;
    /* 0x38 */ void *pbBlock;
} BISMEM;

void func_001184E8(BISMEM *pbis)
{
    pbis->cbRaw = pbis->cbBlock;
    pbis->pbRaw = pbis->pbBlock;
    pbis->cbBlock = 0;
}
