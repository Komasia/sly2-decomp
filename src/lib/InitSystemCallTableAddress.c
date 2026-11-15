// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* InitSystemCallTableAddress (libkernel): locate the kernel's syscall table. Two code signatures are searched
   in kernel memory (0x80000000-0x80080000); each sits at a known distance from the table, so the search is
   advanced until both agree on the same table address. */
#define KERNEL_START 0x80000000
#define KERNEL_END   0x80080000
extern unsigned int D_002C4AA8[4];  /* two (syscall number, handler) pairs to install first */
extern unsigned int D_002C4AA0;     /* syscall table address */
extern unsigned int D_00239558[];   /* signature A: 0x20C bytes past the table */
extern unsigned int D_00239520[];   /* signature B: 0x168 bytes past the table */
void func_002396B0(unsigned int, unsigned int);    /* SetSyscall (syscall 0x74) */
unsigned int FindAddress(unsigned int, unsigned int, unsigned int *);

void InitSystemCallTableAddress(void)
{
    unsigned int addr_a, addr_b, table_a, table_b;
    func_002396B0(D_002C4AA8[0], D_002C4AA8[1]);
    func_002396B0(D_002C4AA8[2], D_002C4AA8[3]);
    addr_a = FindAddress(KERNEL_START, KERNEL_END, D_00239558);
    addr_b = FindAddress(KERNEL_START, KERNEL_END, D_00239520);
    table_a = addr_a - 0x20C;
    table_b = addr_b - 0x168;
    while (table_a != table_b) {
        if (table_a < table_b) {
            addr_a = FindAddress(addr_a + 4, KERNEL_END, D_00239558);
            table_a = addr_a - 0x20C;
        } else {
            addr_b = FindAddress(addr_b + 4, KERNEL_END, D_00239520);
            table_b = addr_b - 0x168;
        }
    }
    D_002C4AA0 = table_a;
}
