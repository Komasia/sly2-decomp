struct R { int cb; int cbAlign; };
struct C { int a[4]; };
struct S { char pad[0x150]; int c; void *pv; };
struct C *__10STACKSCOPE(struct C *);
void *func_001AE378(struct R *);
void LoadSoFromBrx__FP2SOP18CBinaryInputStream(struct S *, void *);
void func_0013C440(struct S *);
void *PvAllocSwCopyImpl__FiPv(struct R *, void *);
void _$_10STACKSCOPE(struct C *, int);
static inline struct R *SetReq(struct R *pr, int cb, int cbAlign) { pr->cb = cb; pr->cbAlign = cbAlign; return pr; }
void func_0013BE58(struct S *p, void *a) {
    struct C ctx;
    struct R req;
    __10STACKSCOPE(&ctx);
    p->pv = func_001AE378(SetReq(&req, 0x580, 0x10));
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(p, a);
    func_0013C440(p);
    p->pv = PvAllocSwCopyImpl__FiPv(SetReq(&req, p->c * 0x2c, 0x10), p->pv);
    _$_10STACKSCOPE(&ctx, 2);
}
