struct X { char pad[8]; float g; float g2; char pad2[8]; float af[9]; };
void func_0014D1F8(struct X *p)
{
    unsigned int i;
    p->g = 1.0f;
    for (i = 0; i < 9; i++) {
        p->g *= p->af[i];
    }
    p->g2 = p->af[8];
}
