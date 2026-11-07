typedef int qword __attribute__((mode(TI)));
struct M { qword a, b, c; };
struct S { char pad[0x40]; M m; qword q70; };
extern "C" {
int CollectRipDraws(S *p, qword q, M m) asm("CollectRipDraws__FP2CMG9VU_VECTORPv");
void func_001CE980(S *p);
void func_001CF518(S *p);
}
void func_001CF518(S *p)
{
    if (!CollectRipDraws(p, p->q70, p->m)) func_001CE980(p);
}
