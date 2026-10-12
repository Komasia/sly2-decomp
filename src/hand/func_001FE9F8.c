struct P { char pad[0x1BC]; float g; };
struct S;
extern struct S D_002BBB60;
float func_0011D948(struct S *, float);
void func_002321E8(int, int);
void func_001FE9F8(struct P *p, float x)
{
    float g = func_0011D948(&D_002BBB60, x);
    int n = (int)(g * 1024.0f);
    if ((int)(p->g * 1024.0f) != n) {
        p->g = g;
        func_002321E8(0x10, n);
    }
}
