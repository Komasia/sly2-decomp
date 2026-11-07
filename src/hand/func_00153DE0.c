struct E { int id; int n; float t; int pad; };
struct S { char pad[0xFC]; int c; struct E a[1]; };
int NDetectState__FP8DETECTORP2LOi(struct S *p, int id, int n);
void SetDetentryState__FP8DETECTORP8DETENTRYi(struct S *p, struct E *pe, int n);
// name: SafeHouse port (UpdateDetector)
void UpdateDetector__FP8DETECTOR(struct S *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->a[i];
        SetDetentryState__FP8DETECTORP8DETENTRYi(p, pe, NDetectState__FP8DETECTORP2LOi(p, pe->id, pe->n));
    }
}
