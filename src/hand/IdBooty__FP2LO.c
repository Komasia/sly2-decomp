/* IdBooty: the id of a booty object's current record (LO +0x158), -1 when it has none. */
struct BOOTYREC {
    /* 0x0 */ int id;
};
struct LO {
    /* 0x000 */ char pad0[0x158];
    /* 0x158 */ struct BOOTYREC *prec;   /* the current record */
};

// name: SafeHouse port (IdBooty, "orig: 0x0013C478 (the current record's id, -1 none)")
int IdBooty__FP2LO(struct LO *plo)
{
    struct BOOTYREC *prec = plo->prec;
    int id = -1;
    if (prec)
        id = prec->id;
    return id;
}
