/* class: CHASEGRAPH (SafeHouse aichase.cpp / aichase.h: the graph's option method 0x10FB48 -> 0x14A178, an entry
 * {kind, oid} appended, at most 0x100). */
struct CHASEENTRY {
    /* 0x0 */ int kind;
    /* 0x4 */ int oid;
    /* 0x8 */ void *plo;
};
struct CHASEGRAPH {
    /* 0x00 */ char pad0[0x54];
    /* 0x54 */ int centry;                 /* field: SafeHouse port (aentry) */
    /* 0x58 */ struct CHASEENTRY *aentry;  /* field: SafeHouse port */
};

void func_0014A178(struct CHASEGRAPH *pgraph, int kind, int oid)
{
    int c = pgraph->centry;
    if (c < 0x100) {
        struct CHASEENTRY *pe = &pgraph->aentry[c];
        pe->kind = kind;
        pe->oid = oid;
        pgraph->centry++;
    }
}
