/* LoadBulkFromBrx (0x20F640): the bulk records: when they are to be loaded, read into stack scratch memory,
 * relocated and taken in (0x170730); otherwise skipped (0x170828 keeps the old ones). */
extern int D_003E1C54;   /* whether to load them */
extern int D_003E1C30;   /* their size */
struct STACKSCOPE { int an[4]; };
struct ALLOCREQ { int cb; int nAlign; int an[2]; };
void Align(void *pbis, int cb) asm("Align__18CBinaryInputStreami");
void __10STACKSCOPE(struct STACKSCOPE *pscope);
void *PvAllocStackImpl__Fi(struct ALLOCREQ *preq);
void Read__18CBinaryInputStreamiPv(void *pbis, int cb, void *pv);
void RelocateBulkRecords__Fi(void *pv);
void func_00170730(void *pshds);
void _$_10STACKSCOPE(struct STACKSCOPE *pscope, int n);
void Skip__18CBinaryInputStreami(void *pbis, int cb);
void func_00170828(void *pshds);
// name: SafeHouse port (LoadBulkFromBrx)
void LoadBulkFromBrx__FP4SHDSP18CBinaryInputStream(void *pshds, void *pbis)
{
    Align(pbis, 0x10);
    if (D_003E1C54) {
        struct STACKSCOPE scope;
        struct ALLOCREQ req;
        void *pv;
        __10STACKSCOPE(&scope);
        { struct ALLOCREQ *preq = &req;
        preq->cb = D_003E1C30;
        preq->nAlign = 0x10;
        pv = PvAllocStackImpl__Fi(preq); }
        Read__18CBinaryInputStreamiPv(pbis, D_003E1C30, pv);
        RelocateBulkRecords__Fi(pv);
        func_00170730(pshds);
        _$_10STACKSCOPE(&scope, 2);
    } else {
        Skip__18CBinaryInputStreami(pbis, D_003E1C30);
        func_00170828(pshds);
    }
}
