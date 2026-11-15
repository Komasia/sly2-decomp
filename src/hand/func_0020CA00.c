/* func_0020CA00 (0x20CA00): a new KIND3 from its slot heap D_003E1AF0 (SafeHouse kind3.cpp). */
extern char D_003E1AF0[];   /* the KIND3 slot heap */
void *func_0011CCC0(void *pslotheap);   /* the slot heap's allocation */

void *func_0020CA00(void)
{
    return func_0011CCC0(D_003E1AF0);
}
