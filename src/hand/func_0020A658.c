/* func_0020A658 (0x20A658): the index of n in a record's list (+0x28 count, +0x2C values), or -1. */
struct LISTREC { char pad[0x28]; int c; int an[1]; };
int func_0020A658(struct LISTREC *prec, int n) { int i; for (i = 0; i < prec->c; i++) if (n == prec->an[i]) return i; return -1; }
