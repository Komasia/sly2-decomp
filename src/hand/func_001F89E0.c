typedef int qword __attribute__((mode(TI)));
struct R { char pad[0x14]; int n14; };
struct P { char pad[0x20]; void *p20; void *p24; };
struct R *PctrlFindXfh__FP7XFBASICiii(struct P *, int, int, int);
void SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(struct R *, qword);
void PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(void *, void *, int, int, int, qword);
// name: SafeHouse port (SetXfhPos)
void SetXfhPos__FP7XFBASICiiG9VU_VECTOR(struct P *p, int n, int m, qword q)
{
    struct R *r = PctrlFindXfh__FP7XFBASICiii(p, 1, n, m);
    if (r) {
        r->n14 = n;
        SetCtrlPos__FP7CTRLPOSG9VU_VECTOR(r, q);
    } else if (n != -1) {
        PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p->p20, p->p24, m, n, 2, q);
    }
}
