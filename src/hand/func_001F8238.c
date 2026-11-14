/* func_001F8238 (called by the splice method 0x100C08): the object's +0xB4 cleared. */
typedef struct LOB4 {
    /* 0x00 */ char pad0[0xb4];
    /* 0xb4 */ int nB4;
} LOB4;

void func_001F8238(LOB4 *plo)
{
    plo->nB4 = 0;
}
