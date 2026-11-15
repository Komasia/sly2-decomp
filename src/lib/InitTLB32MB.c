// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* InitTLB32MB (libkernel): program the TLB on a 32 MB console from the kernel/default/extended entry tables;
   the kernel and default entries are wired. Unused entries are pointed at an unmapped region. Returns the
   number of entries written. */
#define TLB_ENTRIES 48
typedef struct { unsigned int PageMask, EntryHi, EntryLo0, EntryLo1; } TLBENT;
typedef struct {
    int nKernel, nDefault, nExtended, nWired;
    TLBENT *pKernel, *pDefault, *pExtended;
} TLBINFO;
extern TLBINFO D_002C6098;
extern char D_002AAD98[];   /* "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n" */
extern char D_002AADD0[], D_002AADE8[], D_002AAE00[];  /* "# TLB over flow (1)" .. "(3)" */
int func_002369E0(const char *, ...);   /* kernel printf (Kprintf) */
void func_002398D0(int);                /* exit with status */
void SetTLBEntry(int, unsigned int, unsigned int, unsigned int, unsigned int);  /* SetTLBEntry (syscall 0x56) */

int InitTLB32MB(void)
{
    register int i __asm__("$25"); /* the original keeps the TLB index in $t9 across calls */
    int n;
    int j;
    TLBENT *ent;

    func_002369E0(D_002AAD98, D_002C6098.nKernel - 1, D_002C6098.nKernel,
                  D_002C6098.nKernel + D_002C6098.nDefault - 1,
                  D_002C6098.nKernel + D_002C6098.nDefault,
                  D_002C6098.nKernel + D_002C6098.nDefault + D_002C6098.nExtended - 1);
    __asm__ __volatile__("mtc0 $0, $6\n\tsync.p");    /* Wired = 0 */

    i = 0;
    n = D_002C6098.nKernel;
    if (n > TLB_ENTRIES) {
        func_002369E0(D_002AADD0);
        func_002398D0(1);
    }
    ent = D_002C6098.pKernel;
    for (; i < n; i++, ent++)
        SetTLBEntry(i, ent->PageMask, ent->EntryHi, ent->EntryLo0, ent->EntryLo1);

    n = i + D_002C6098.nDefault;
    if (n > TLB_ENTRIES) {
        func_002369E0(D_002AADE8);
        func_002398D0(1);
    }
    ent = D_002C6098.pDefault;
    for (; i < n; i++, ent++)
        SetTLBEntry(i, ent->PageMask, ent->EntryHi, ent->EntryLo0, ent->EntryLo1);

    D_002C6098.nWired = i;
    __asm__ __volatile__("mtc0 %0, $6\n\tsync.p" : : "r"(i));    /* Wired = i */

    if (D_002C6098.nExtended > 0) {
        n = i + D_002C6098.nExtended;
        if (n > TLB_ENTRIES) {
            func_002369E0(D_002AAE00);
            func_002398D0(1);
        }
        ent = D_002C6098.pExtended;
        for (; i < n; i++, ent++)
            SetTLBEntry(i, ent->PageMask, ent->EntryHi, ent->EntryLo0, ent->EntryLo1);
    }
    for (j = i; j < TLB_ENTRIES; j++)
        SetTLBEntry(j, 0, 0xE0000000 + (j << 13), 0, 0);
    return i;
}
