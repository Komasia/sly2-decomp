/* func_001EC7E8 (called by UnloadWorld): the module's world state cleared - D_003DA790, D_003DCFA0 and the 0x40
 * bytes at D_003DCFA8. */
extern int D_003DA790;
extern int D_003DCFA0;
extern char D_003DCFA8[];
void *memset(void *pv, int b, unsigned int cb);

void func_001EC7E8(void)
{
    D_003DA790 = 0;
    D_003DCFA0 = 0;
    memset(D_003DCFA8, 0, 0x40);
}
