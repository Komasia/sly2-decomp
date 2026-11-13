// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
void kputchar(int c);
void serialPutchar(int c)
{
    if (c == '\n') {
        kputchar('\r');
        kputchar('\n');
        return;
    }
    kputchar(c);
}
