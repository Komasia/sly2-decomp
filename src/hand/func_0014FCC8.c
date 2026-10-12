struct G { char pad[0x24]; float f24; char pad2[0x24]; float f4c; };
extern struct G D_002DDF40;
struct T { int a; float b; float c; };
void func_0014FCC8(struct T *p, int a)
{
    p->a = a;
    p->c = D_002DDF40.f4c;
    p->b = D_002DDF40.f24;
}
