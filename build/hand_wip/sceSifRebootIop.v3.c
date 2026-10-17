// (Claude agent) v3 aligned 13 (v2 27): strlen as `p = img; while (*p) p++; if ((unsigned)(p + 11 - img) > 80)` (gives target p-(img-11)),
// strcpy via block-scoped q then d = q. Left: loop-1 regs (target d=v1, byte a0, hoisted *img a1; ours q=a0, byte a1, hoisted a2 + q->d copy).
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
    const char *p = img;
    while (*p) p++;
    if ((unsigned int)(p + 11 - img) > 80) {
        func_00236960(D_002AACE0, img);
        return 0;
    }
    func_00236A60(0);
    func_00236C00();
    { char *q = param;
    while (*s) *q++ = *s++;
    d = q; }
    while (*img) *d++ = *img++;
    *d = 0;
    return func_00239198(param, 0);
}
