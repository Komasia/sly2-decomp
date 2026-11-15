// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* __pure_virtual (libgcc): target of pure virtual vtable slots; a call is fatal. */
void __terminate(void);
void __pure_virtual(void)
{
    __terminate();
}
