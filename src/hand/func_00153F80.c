struct E { int id; int n; float t; int pad; };
struct S { char pad[0xFC]; int c; struct E a[1]; };
struct E *PdetentryFind__FP8DETECTORi(struct S *p, int id);
void SetDetentryState__FP8DETECTORP8DETENTRYi(struct S *p, struct E *pe, int n);
void s1_memmove(void *dst, void *src, int cb);
// name: SafeHouse port (RemoveDetectorTarget)
void RemoveDetectorTarget__FP8DETECTORi(struct S *p, int id)
{
    struct E *pe = PdetentryFind__FP8DETECTORi(p, id);
    if (pe) {
        SetDetentryState__FP8DETECTORP8DETENTRYi(p, pe, 0);
        p->c--;
        s1_memmove(pe, pe + 1, (&p->a[p->c] - pe) * sizeof(struct E));
    }
}
