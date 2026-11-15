/* func_001A6B30 (0x1A6B30): the plain LO's matrix query: fills *pmat (if given) with the identity and returns the
 * static matrix D_002C44F0. */
struct M { float a[16]; };
extern struct M g_matLoDefault __asm__("D_002C44F0");
void s1_memset(void *p, int c, int n) asm("memset");
struct M *func_001A6B30(void *plo, struct M *pmat)
{
    if (pmat) {
        s1_memset(pmat, 0, 0x40);
        pmat->a[0] = pmat->a[5] = pmat->a[10] = pmat->a[15] = 1.0f;
    }
    return &g_matLoDefault;
}
