struct P { char pad[0x88]; int a[6]; char pad2[0x3BC - 0xA0]; int fl; };
void func_001FB658(struct P *, int, int);
static inline int Norm(int deg) { int n = deg % 360; return n > -1 ? n : n + 360; }
void func_001FC380(struct P *p, unsigned int k, int deg)
{
    if (k < 6) {
        int n = Norm(deg);
        if (n != p->a[k]) {
            p->fl |= 1 << k;
            p->a[k] = n;
            func_001FB658(p, 0x100, 0x100);
        }
    }
}
