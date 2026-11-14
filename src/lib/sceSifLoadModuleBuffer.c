// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* libkernel loadfile: load an IRX module from an IOP memory buffer (the game passes the IOP heap block it copied the
   module into); the result code of the module start is dropped. */
int _sceSifLoadModuleBuffer(void *addr, int args, const char *argp, int *result);
int sceSifLoadModuleBuffer(void *addr, int args, const char *argp)
{
    int r;
    return _sceSifLoadModuleBuffer(addr, args, argp, &r);
}
