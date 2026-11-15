/* The booty's load: room for 32 records (0x2C bytes) on the stack while the SO loads (EOPID 1152 adds them), 0x13C440,
 * then the records copied to the world heap at their real count. Layout: SafeHouse port (booty.cpp). */
struct AREQ { int cb; int cbAlign; };
struct STACKSCOPE { int pbis[4]; };
struct BOOTY { char pad[0x150]; int crec; void *arec; };   /* field: SafeHouse port (booty.cpp: 0x2C-byte records at +0x154) */
struct STACKSCOPE *__10STACKSCOPE(struct STACKSCOPE *);
void *PvAllocStackClearImpl__Fi(struct AREQ *);
void LoadSoFromBrx__FP2SOP18CBinaryInputStream(struct BOOTY *, void *);
void func_0013C440(struct BOOTY *);
void *PvAllocSwCopyImpl__FiPv(struct AREQ *, void *);
void _$_10STACKSCOPE(struct STACKSCOPE *, int);
static inline struct AREQ *SetReq(struct AREQ *pr, int cb, int cbAlign) { pr->cb = cb; pr->cbAlign = cbAlign; return pr; }
void func_0013BE58(struct BOOTY *pbooty, void *pbis) {
    struct STACKSCOPE ss;
    struct AREQ req;
    __10STACKSCOPE(&ss);
    pbooty->arec = PvAllocStackClearImpl__Fi(SetReq(&req, 0x580, 0x10));
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(pbooty, pbis);
    func_0013C440(pbooty);
    pbooty->arec = PvAllocSwCopyImpl__FiPv(SetReq(&req, pbooty->crec * 0x2c, 0x10), pbooty->arec);
    _$_10STACKSCOPE(&ss, 2);
}
