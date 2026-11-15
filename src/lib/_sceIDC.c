// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder
/* _sceIDC (libkernel): Invalidate (DXIN) every data-cache line holding an address in [start, end]. Each of the
   64 sets (2 ways) is checked by loading its tag (DXLTG into TagLo). */
#define DCACHE_SIZE 0x1000      /* per way */
#define DCACHE_LINE 0x40
void _sceIDC(unsigned int start, unsigned int end)
{
    int line;
    unsigned int tag;
    for (line = 0; line < DCACHE_SIZE; line += DCACHE_LINE) {
        __asm__ volatile("sync\n\tcache 0x10,0(%0)\n\tsync" : : "r"(line));
        __asm__ volatile("mfc0 %0,$28" : "=r"(tag));
        tag = (tag & 0xFFFFF000) + line;
        if (tag >= start && tag <= end) {
            __asm__ volatile("sync\n\tcache 0x16,0(%0)\n\tsync" : : "r"(line));
        }
        __asm__ volatile("sync\n\tcache 0x10,1(%0)\n\tsync" : : "r"(line));
        __asm__ volatile("mfc0 %0,$28" : "=r"(tag));
        tag = (tag & 0xFFFFF000) + line;
        if (tag >= start && tag <= end) {
            __asm__ volatile("sync\n\tcache 0x16,1(%0)\n\tsync" : : "r"(line));
        }
        __asm__ volatile("sync");
    }
}
