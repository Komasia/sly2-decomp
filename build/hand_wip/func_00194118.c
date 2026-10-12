extern char D_002BF670[];
struct T { char pad[0xFC]; int fc, x100, x104, x108, x10c, x110; void *x114; int x118, x11c, x120, x124, x128, x12c, x130, x134, x138, x13c, x140;
  char pad2[0x164-0x144]; int x164, x168, x16c; };
struct S { char pad[0x68]; struct T *p; };
void func_00194118(struct S *s) {
    struct T *t = s->p;
    t->x164 = 5; //P
    t->x114 = D_002BF670; //P
    t->x168 = 1; //P
    t->x128 = 3; //P
    t->x140 = 0; //P
    t->x100 = 0; //P
    t->fc = 0; //P
    t->x108 = 0; //P
    t->x10c = 0; //P
    t->x110 = 1; //P
    t->x120 = 0; //P
    t->x124 = 0; //P
    t->x16c = 0; //P
    t->x130 = 0; //P
}
