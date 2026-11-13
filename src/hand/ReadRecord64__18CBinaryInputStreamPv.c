/* CBinaryInputStream::ReadRecord64: a 64-byte record (a file key record) read. */
struct CBinaryInputStream;
void Read(struct CBinaryInputStream *pbis, int cb, void *pv) asm("Read__18CBinaryInputStreamiPv");

// name: SafeHouse port (CBinaryInputStream::ReadRecord64, bis.h)
void ReadRecord64__18CBinaryInputStreamPv(struct CBinaryInputStream *pbis, void *pv)
{
    Read(pbis, 0x40, pv);
}
