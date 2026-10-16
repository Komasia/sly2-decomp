// WIP (Claude agent): far (52 diffs). inline strlen/strcpy/strcat shapes differ; target strlen compares p-(img-11) <u 81; short loops need gnu-reorg or empty asm.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorg
// SLY2_SAVES: sd
extern char D_002AACD0[];
extern char D_002AACE0[];
int func_00236960(const char *, ...);
void func_00236A60(int);
int func_00236C00(void);
int func_00239198(const char *, int);
static inline unsigned int _strlen(const char *s)
{
    const char *p = s;
    while (*p) { __asm__ volatile(""); p++; }
    return p - s;
}
int sceSifRebootIop(const char *img)
{
    char param[80];
    char *s = D_002AACD0;
    char *d;
    if (_strlen(img) + 11 > 80) {
        func_00236960(D_002AACE0, img);
        return 0;
    }
    func_00236A60(0);
    func_00236C00();
    d = param;
    while (*s) *d++ = *s++;
    {
        char c;
        while ((c = *img) != 0) { *d++ = c; img++; }
    }
    *d = 0;
    return func_00239198(param, 0);
}
