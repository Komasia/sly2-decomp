struct A { char pad[0x60]; int n; };
void func_002333B4(void *p, int c, int cb);
int func_001F3FB0(struct A *p, float *pm)
{
    if (pm) {
        func_002333B4(pm, 0, 0x40);
        pm[0] = pm[5] = pm[10] = pm[15] = 1.0f;
    }
    return p->n;
}
