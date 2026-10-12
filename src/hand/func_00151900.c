struct G { char pad[0x24]; float g24; };
extern struct G D_002DDF40;
struct B { char pad[0x1BC]; float g; };
void func_0014FCC8(void *a, struct B *b);
void func_0014F610(struct G *pg, float g);
void func_00151900(void *a, struct B *b)
{
    struct G *pg;
    func_0014FCC8(a, b);
    pg = &D_002DDF40;
    func_0014F610(pg, 49.0f);
    pg->g24 = b->g;
}
