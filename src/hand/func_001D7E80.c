struct X { short a; signed char b; char c; unsigned short h; };
struct T { struct X *px; int n; };
extern int D_002C2D90[];
void func_001D7DA0(void *a, void *b, struct T *pt);
char *func_001D7E80(void *a, void *b, char *pb) {
    struct T t;
    func_001D7DA0(a, b, &t);
    return pb + (t.px->h + t.n * D_002C2D90[t.px->b]);
}
