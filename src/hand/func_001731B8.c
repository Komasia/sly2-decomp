typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct MK { int a[4]; };
struct AI { int cb; int align; };
struct S { char pad[0x50]; int c50; void *p54; char pad2[0x94 - 0x58]; void *p94; int c98; void *p9C; };
struct MK *__10STACKSCOPE(struct MK *pm);
void _$_10STACKSCOPE(struct MK *pm, int n);
void *PvAllocStackClearImpl__Fi(struct AI *pa);
void *PvAllocStackImpl__Fi(struct AI *pa);
void *PvAllocSwCopyImpl__FiPv(struct AI *pa, void *pv);
void func_001733C8(struct S *p, qword q);
void LoadLoFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *pv);
static inline struct AI *SetAi(struct AI *pa, int cb, int align) { pa->cb = cb; pa->align = align; return pa; }
void func_001731B8(struct S *p, void *pv) {
    struct MK mk;
    struct AI ai;
    __10STACKSCOPE(&mk);
    p->p54 = PvAllocStackClearImpl__Fi(SetAi(&ai, 0xE00, 0x10));
    p->p9C = PvAllocStackImpl__Fi(SetAi(&ai, 0x100, 0x10));
    p->p94 = PvAllocStackImpl__Fi(SetAi(&ai, 0x20, 0x10));
    func_001733C8(p, D_002A2DD0);
    LoadLoFromBrx__FP2LOP18CBinaryInputStream(p, pv);
    p->p54 = PvAllocSwCopyImpl__FiPv(SetAi(&ai, p->c50 * 0x1C, 0x10), p->p54);
    { void *pv9C = PvAllocSwCopyImpl__FiPv(SetAi(&ai, p->c98 << 4, 0x10), p->p9C); void *pv94 = p->p94; p->p9C = pv9C; p->p94 = PvAllocSwCopyImpl__FiPv(SetAi(&ai, 0x20, 0x10), pv94); }
    _$_10STACKSCOPE(&mk, 2);
}
