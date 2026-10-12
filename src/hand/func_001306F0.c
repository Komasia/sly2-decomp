struct ASEGA { char pad[0x2c]; struct ASEGA *pnext; };
struct S { char pad[0x50]; struct ASEGA *pfirst; char pad2[0x24]; float f78; };
void func_00131A20(struct ASEGA *, float);
void func_001306F0(struct S *p, float g) {
    struct { void *a, *b; int c; void *d; } dli;
    struct ASEGA *pa;
    for (pa = p->pfirst; pa; pa = pa->pnext) func_00131A20(pa, g);
    p->f78 = g;
}
