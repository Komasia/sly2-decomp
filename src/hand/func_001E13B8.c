struct CMD { int kind; int b; int n8; int nC; int n10; int n14; int n18; int n1C; };
struct CMDF { int kind; int b; int n8; int nC; int n10; int n14; float g18; int n1C; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E13B8(void *pq, int a, int b, int c, int d)
{
    struct CMD *p = func_001E01F8(pq, 0x3B, d);
    p->n10 = a; p->n14 = b; p->n18 = c;
}
