// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceSifRebootIop (libkernel): reboot the IOP with the module image `img`: reset through "rom0:UDNL <img>"
   after shutting down the RPC layer. Returns 0 if the path is too long, else sceSifResetIop's result. */
#define RESET_ARG_MAX 80
extern char D_002AACD0[];   /* "rom0:UDNL " */
extern char D_002AACE0[];   /* "too long parameter '%s'\n" */
int scePrintf(const char *, ...);
void sceSifInitRpc(int);
void func_00236C00(void);   /* sceSifExitRpc */
int sceSifResetIop(const char *, int);
int sceSifRebootIop(const char *img)
{
    char param[RESET_ARG_MAX];
    char *s = D_002AACD0;      /* copy the prefix, then the image path */
    register char *d asm("$3");
    register int check asm("$2");
    int byte;
    const char *p = img;
    unsigned int origin;
    if (*p) {
        origin = (unsigned int)img - 11;
        do { ++p; } while (*p);
    } else {
        origin = (unsigned int)img - 11;
    }
    if ((unsigned int)p - origin > RESET_ARG_MAX) {
        scePrintf(D_002AACE0, img);
        return 0;
    }
    sceSifInitRpc(0);
    func_00236C00();
    {
        register char *q asm("$3") = param;
        while ((check = *s) != 0)
            *q++ = *s++;
        d = q;
    }
    byte = (unsigned char)*img;
    if (byte) do {
        *d++ = byte;
        check = *++img;
        byte = check;
    } while (check);
    *d = 0;
    return sceSifResetIop(param, 0);
}
