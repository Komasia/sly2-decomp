typedef unsigned long ulong;
struct E { char pad[0x10]; ulong lo : 48; ulong b48 : 1; ulong hi : 15; char pad2[0xB0 - 0x18]; };
struct P { char pad[0xE0]; int c; struct E *ae; };
void func_001F68A8(struct P *p, int f)
{
    int i;
    for (i = 0; i < p->c; i++) p->ae[i].b48 = f;
}
