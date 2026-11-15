/* func_0020C010 (0x20C010): a new KIND2 from its slot heap D_003E1AD8 (SafeHouse kind2.cpp). */
extern char D_003E1AD8[];   /* the KIND2 slot heap */
void *func_0011CCC0(void *pslotheap);   /* the slot heap's allocation */

void *func_0020C010(void)
{
    return func_0011CCC0(D_003E1AD8);
}
