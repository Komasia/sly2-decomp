// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
/* GetRomName (libkernel): read the console's ROM version string (rom0:ROMVER, e.g. "0160EC20010704")
   once and cache it. */
#define ROMVER_LEN 14
extern char D_002C8378[];   /* cached ROMVER text; empty until the first call */
int sceOpen(const char *, int);
int sceRead(int, void *, int);
int sceClose(int);

char *GetRomName(void)
{
    int fd;
    if (D_002C8378[0] == 0) {
        fd = sceOpen("rom0:ROMVER", 1 /* SCE_RDONLY */);
        if (fd >= 0) {
            sceRead(fd, D_002C8378, ROMVER_LEN);
            sceClose(fd);
        }
    }
    return D_002C8378;
}
