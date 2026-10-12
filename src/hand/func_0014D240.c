/* near-miss: target materialises 0xFFFFFFFF mask as addiu -1; dsrl32 (assembler dli expansion?), ours lui 0xFFFF; dsrl32 */
struct T { char pad[0x50]; unsigned long last; int hi; };
unsigned long func_0014D240(struct T *p)
{
    unsigned long c;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(c));
    c &= 0xFFFFFFFF;
    if (c < p->last) p->hi++;
    p->last = c;
    return ((unsigned long)p->hi << 32) | c;
}
