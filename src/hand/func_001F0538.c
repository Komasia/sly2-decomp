/* class: CID_88, SMA - a state machine running on an object (vtable 0x2D9768, SafeHouse smrun.h; vt slot 2): one
 * reference fewer; at none, its references dropped and the SMA back to its pool (D_003E1278). */
struct SMA {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ char sub4[0xc];
    /* 0x10 */ int cref;   /* field: SafeHouse port */
};
extern char D_003E1278[];   /* the SMAs' pool (SafeHouse smrun.h) */
void func_00256EE0(struct SMA *psma, void *p);   /* a reference-counted pointer assignment (r7_candidates) */
void func_002580A8(void *p, void *pNew);
void func_001334A8(struct SMA *psma);
void func_0011CD98(void *ppool, struct SMA *psma);   /* back to the pool */

void func_001F0538(struct SMA *psma, int n)
{
    int cref = psma->cref - 1;
    psma->cref = cref;
    if (cref <= 0) {
        func_00256EE0(psma, 0);
        func_002580A8(psma->sub4, 0);
        func_001334A8(psma);
        func_0011CD98(D_003E1278, psma);
    }
}
