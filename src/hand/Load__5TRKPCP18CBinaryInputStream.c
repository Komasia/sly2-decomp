/* TRKPC::Load: a constant position track reads its position (12 bytes at +0x4). TRKPC: SafeHouse port (aseg.h). */
struct CBinaryInputStream;
struct VECTOR3 { float x, y, z; };
struct TRKPC {
    /* 0x0 */ void *pvtbl;
    /* 0x4 */ struct VECTOR3 pos;   /* field: SafeHouse port */
};
void Read(struct CBinaryInputStream *pbis, int cb, void *pv) asm("Read__18CBinaryInputStreamiPv");

// name: SafeHouse port (TRKPC::Load)
void Load__5TRKPCP18CBinaryInputStream(struct TRKPC *ptrk, struct CBinaryInputStream *pbis)
{
    Read(pbis, 0xC, &ptrk->pos);
}
