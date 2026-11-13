extern int D_003E1C54;
extern int D_003E1C30;
struct L { int a[4]; };
struct M { int a; int b; int c[2]; };
void Align(void *q, int n) asm("Align__18CBinaryInputStreami");
void __10STACKSCOPE(struct L *pl);
void *PvAllocStackImpl__Fi(struct M *pm);
void Read__18CBinaryInputStreamiPv(void *q, int a, void *x);
void RelocateBulkRecords__Fi(void *x);
void func_00170730(void *p);
void _$_10STACKSCOPE(struct L *pl, int n);
void Skip__18CBinaryInputStreami(void *q, int a);
void func_00170828(void *p);
// name: SafeHouse port (LoadBulkFromBrx)
void LoadBulkFromBrx__FP4SHDSP18CBinaryInputStream(void *p, void *q)
{
    Align(q, 0x10);
    if (D_003E1C54) {
        struct L l;
        struct M m;
        void *x;
        __10STACKSCOPE(&l);
        { struct M *pm = &m;
        pm->a = D_003E1C30;
        pm->b = 0x10;
        x = PvAllocStackImpl__Fi(pm); }
        Read__18CBinaryInputStreamiPv(q, D_003E1C30, x);
        RelocateBulkRecords__Fi(x);
        func_00170730(p);
        _$_10STACKSCOPE(&l, 2);
    } else {
        Skip__18CBinaryInputStreami(q, D_003E1C30);
        func_00170828(p);
    }
}
