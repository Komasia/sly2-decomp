struct K { int a; int b; };
struct E { int a; int b; struct K k1; struct K k2; struct K k3; struct K k4; };
struct S { char pad[0x270]; struct E ae[5]; };
void func_00181330(struct S *p, unsigned int i, struct K *pk1, struct K *pk2)
{
    if (i < 5) {
        struct E *pe = &p->ae[i];
        pe->a = 1;
        pe->k1 = *pk1;
        pe->k2 = *pk2;
    }
}
