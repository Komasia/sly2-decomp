struct X { short a; signed char b; char c; unsigned short h; };
struct T { struct X *px; int n; };
extern int D_002C2D90[];
void FFindEntryKey__FP4TRIEPP4PENTPi(void *a, void *b, struct T *pt);
char *func_001D7E80(void *a, void *b, char *pb) {
    struct T t;
    FFindEntryKey__FP4TRIEPP4PENTPi(a, b, &t);
    return pb + (t.px->h + t.n * D_002C2D90[t.px->b]);
}
