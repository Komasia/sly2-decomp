/* func_00172888: the qsort order of search places: by their bearing (+0x10). */
struct S { char pad[0x10]; float g10; };
int func_00172888(struct S *a, struct S *b) { return a->g10 < b->g10; }
