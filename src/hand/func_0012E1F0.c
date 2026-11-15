/* A new controller slot from the controller slot heap D_003E123C (0x20..0x80-byte controllers, SafeHouse xf.h). */
extern char D_003E123C[];
void *func_0011CCC0(void *pslotheap);   /* the slot heap's allocation */

void *func_0012E1F0(void)
{
    return func_0011CCC0(D_003E123C);
}
