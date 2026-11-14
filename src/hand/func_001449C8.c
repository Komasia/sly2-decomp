/* class: ACTOR (called by UpdateActor): an accessor of a record's +0x28. */
struct ACTORREC {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int n28;
};

int func_001449C8(struct ACTORREC *prec)
{
    return prec->n28;
}
