// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* checkModelVersion (libcdvd): read the ROM version string; nonzero if its build date (the 8 digits before
   the end) is after 2001-06-08. Returns -1 if rom0:ROMVER cannot be opened. */
extern char D_002AB320[];   /* "rom0:ROMVER" */
int sceOpen(const char *, int, ...);
int sceRead(int, void *, int);
int sceClose(int);
int atoi(const char *);
int checkModelVersion(void)
{
    int fd;
    unsigned int i;
    char *p;
    char buf[256];
    fd = sceOpen(D_002AB320, 1);
    if (fd < 0) return -1;
    for (i = 0, p = buf; i < 256; i++) {
        sceRead(fd, p, 1);
        if (*p++ == 0) break;
    }
    sceClose(fd);
    return atoi(&buf[i - 9]) > 20010608;
}
