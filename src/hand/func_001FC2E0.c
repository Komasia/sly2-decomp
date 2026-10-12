struct P { char pad[0x70]; float a[6]; char pad2[0x3BC - 0x88]; int fl; };
struct S;
extern struct S D_002BBB60;
float func_0011D948(struct S *, float);
void func_001FB658(struct P *, int, int);
void func_001FC2E0(struct P *p, unsigned int k, float g)
{
    if (k < 6) {
        float f = func_0011D948(&D_002BBB60, g);
        if ((int)(f * 1024.0f) != (int)(p->a[k] * 1024.0f)) {
            p->fl |= 1 << k;
            p->a[k] = f;
            func_001FB658(p, 0x80, 0x80);
        }
    }
}
