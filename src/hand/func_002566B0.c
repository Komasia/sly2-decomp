/* class: a Splice library object (a vtable entry at 0x2CA684, next to 0x256658): 4 bytes read from the stream into
 * the second argument (Read__18CBinaryInputStreamiPv). */
typedef struct CBinaryInputStream CBinaryInputStream;
void Read__18CBinaryInputStreamiPv(CBinaryInputStream *pbis, int cb, void *pv);

void func_002566B0(void *p, void *pv, CBinaryInputStream *pbis)
{
    Read__18CBinaryInputStreamiPv(pbis, 4, pv);
}
