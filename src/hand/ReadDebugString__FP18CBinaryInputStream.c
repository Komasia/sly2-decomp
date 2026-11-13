/* ReadDebugString: skip a debug string in a binary stream: its 16-bit length, then that many bytes (read into
 * nothing). */
struct CBinaryInputStream;
int U16Read(struct CBinaryInputStream *pbis) asm("U16Read__18CBinaryInputStream");
void Read(struct CBinaryInputStream *pbis, int cb, void *pv) asm("Read__18CBinaryInputStreamiPv");

// name: SafeHouse port (ReadDebugString)
void ReadDebugString__FP18CBinaryInputStream(struct CBinaryInputStream *pbis)
{
    Read(pbis, U16Read(pbis), 0);
}
