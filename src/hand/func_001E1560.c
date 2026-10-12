struct CMD { int kind; int b; int n8; int nC; int n10; int n14; int n18; int n1C; };
struct CMDF { int kind; int b; int n8; int nC; float g10; float g14; int n18; int n1C; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E1560(void *pq, int a, int b)
{
    struct CMD *p = func_001E01F8(pq, 0x42, 0);
    if (a == -1) a = 0x40;
    p->n10 = a; p->n14 = b;
}
