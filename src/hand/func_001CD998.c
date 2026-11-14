struct E { int a, b; int c[2]; };
extern struct E *D_003D4A50;
void *s1_memset(void *p, int c, int n) asm("memset");
struct E *func_001CD998(void)
{
    /*B*/s1_memset(D_003D4A50->c, 0, 8); return D_003D4A50++;/*E*/
}
