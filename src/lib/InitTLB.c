// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* InitTLB (libkernel): set up the TLB; 32 MB consoles use the table-driven InitTLB32MB. */
int GetMemorySize(void);
void InitTLB32MB(void);
void _InitTLB(void);

void InitTLB(void)
{
    if (GetMemorySize() == 32 * 1024 * 1024) InitTLB32MB();
    else _InitTLB();
}
