struct T { char pad[0xCC]; int a[1]; };
extern struct G g_sw;
int func_0013E368(struct G *g, int x);
void s1_strcpy(void *p, int v) asm("strcpy");
void func_00211348(void *p, int i, struct T *t)
{
    s1_strcpy(p, func_0013E368(&g_sw, t->a[i]));
}
