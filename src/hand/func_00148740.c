struct E { char b[0x44]; };
struct X { int a; struct E ae[2]; };
void RunTriggerAsegList__FP2LOPv(struct E *e, int a);
void func_00148740(struct X *p)
{
    unsigned int i;
    for (i = 0; i < 2; i++) RunTriggerAsegList__FP2LOPv(&p->ae[i], p->a);
}
