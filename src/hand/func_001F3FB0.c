struct A { char pad[0x60]; int n; };
void s1_memset(void *p, int c, int cb) asm("memset");
int func_001F3FB0(struct A *p, float *pm)
{
    if (pm) {
        s1_memset(pm, 0, 0x40);
        pm[0] = pm[5] = pm[10] = pm[15] = 1.0f;
    }
    return p->n;
}
