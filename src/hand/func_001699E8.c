struct A { int a[5]; };
struct B { int a[10]; };
struct C { int a[6]; };
void LoadGlobSubmeshFromBrx__FP7GLOBSETP18CBinaryInputStreamPvP6SPHEREN22T3iPiPP4FACEP6STREAM(void *p, struct A *pa0, struct B *pb0, struct C *pc0, struct A *pa, struct B *pb, struct C *pc, int x, int y, int z, int w);
// name: SafeHouse port (LoadGlobSubmeshesFromBrx)
void LoadGlobSubmeshesFromBrx__FP7GLOBSETP18CBinaryInputStreamPvT2iiiii(void *p, struct A *aa, struct B *ab, struct C *ac, int c, int x, int y, int z, int w)
{
    int i;
    for (i = 0; i < c; i++) {
        struct A *pa = &aa[i + 1];
        struct B *pb = &ab[i + 1];
        struct C *pcw = ac ? ac + i + 1 : 0;
        LoadGlobSubmeshFromBrx__FP7GLOBSETP18CBinaryInputStreamPvP6SPHEREN22T3iPiPP4FACEP6STREAM(p, aa, ab, ac, pa, pb, pcw, x, y, z, w);
    }
}
