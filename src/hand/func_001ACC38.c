struct H { char pad[0xFD50]; int x; };
extern struct H D_002E65E0;
struct CLOCK { float t; float dt; char pad[0x34]; float t3c; };
extern struct CLOCK D_002DDED0;
struct S { char pad[0x44]; int x44; float x48; };
void func_001ACC38(struct S *p, int n)
{
    if (n == p->x44) return;
    switch (n) { case 2: case 3: D_002E65E0.x = 0; }
    p->x44 = n;
    p->x48 = D_002DDED0.t3c;
}
