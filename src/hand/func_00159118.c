typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword aq[4]; } M4;
typedef struct B7 { qword aq[7]; } B7;
extern M4 D_002DE5B0;
extern B7 D_002DE5F0;
struct S { int a; int b; int pad[2]; M4 m; B7 b7; char pad2[0x100 - 0xC0]; };
void *s1_memset(void *pv, int b, int cb);
// name: SafeHouse port (InitEmitb)
void InitEmitb__FP5EMITB(struct S *p)
{
    s1_memset(p, 0, sizeof(struct S));
    p->a = 1;
    p->b = -1;
    p->m = D_002DE5B0;
    p->b7 = D_002DE5F0;
}
