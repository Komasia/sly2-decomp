typedef int qword __attribute__((mode(TI)));
struct M { qword a, b, c; };
struct S { char pad[0x40]; M m; qword q70; char pad2[0xF0 - 0x80]; void *p; };
extern "C" {
qword PosConvertXfs(void *p, int n, qword q) asm("PosConvertXfs__FP2XFT0G9VU_VECTOR");
M MatConvertXfs(void *p, int n, M *pm) asm("MatConvertXfs__FP2XFT0P7MATRIX3Pv");
int CollectRipDraws(S *p, qword q, M m) asm("CollectRipDraws__FP2CMG9VU_VECTORPv");
void func_001CFA40(S *p);
}
void func_001CFA40(S *p)
{
    qword q = PosConvertXfs(p->p, 0, p->q70);
    M m;
    m = MatConvertXfs(p->p, 0, &p->m);
    CollectRipDraws(p, q, m);
}
