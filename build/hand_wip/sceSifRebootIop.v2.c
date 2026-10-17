// WIP (Claude agent, 2026-10-17): ee-gcc 2.9 gives the target loop shapes (strcat loop now exact form). Remaining: target computes strlen+11 as p-(img-11) with img-11 hoisted to the loop preheader and duplicated on the loop-skip path; strcpy preheader preloads *img into a1 and copies to a0.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern char D_002AACD0[];
extern char D_002AACE0[];
int func_00236960(const char *, ...);
void func_00236A60(int);
int func_00236C00(void);
int func_00239198(const char *, int);
static inline unsigned int _strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
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
    while (*img) *d++ = *img++;
    *d = 0;
    return func_00239198(param, 0);
}
