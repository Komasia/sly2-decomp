typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x240]; qword pos; };
qword PosOfLo__FP2LO(void *p);
void func_001FF4F0(void *a, struct P *p, qword *pv)
{
    qword a0, r;
    if (pv) {
        a0 = PosOfLo__FP2LO(a);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a0), "j"(p->pos));
        *pv = r;
    }
}
