typedef int qword __attribute__((mode(TI)));
struct M { qword a, b, c; };
struct S { char pad[0x40]; M m; qword q70; };
extern "C" {
int func_001CF338(S *p, qword q, M m);
void func_001CE980(S *p);
void func_001CF518(S *p);
}
void func_001CF518(S *p)
{
    if (!func_001CF338(p, p->q70, p->m)) func_001CE980(p);
}
