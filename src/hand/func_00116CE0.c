/* func_00116CE0: byte comparison of two 0xC-byte keys (memcmp), one of the 16-byte entries
 * of the table at 0x2BBA90 (func_00116CA0 .. func_00116D00: 4, 8, 12 and 16-byte keys). */
int memcmp(const void *pv0, const void *pv1, unsigned int cb);

int func_00116CE0(const void *pv0, const void *pv1)
{
    return memcmp(pv0, pv1, 0xC);
}
