struct CMD { int kind; int b; int n8; int nC; int n10; int n14; int n18; int n1C; };
struct CMDF { int kind; int b; int n8; int nC; float g10; float g14; int n18; int n1C; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E0B40(void *pq, int a, int b, float g)
{
    struct CMDF *p = (struct CMDF *)func_001E01F8(pq, 0x23, 0);
    p->g10 = g; ((struct CMD *)p)->n14 = a; p->n18 = b;
}
