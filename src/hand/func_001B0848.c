struct G { char pad[0xFD50]; int f; };
extern struct G D_002E65E0;
void func_001B0848(int *p)
{
    if (D_002E65E0.f) { *p = 0x47; return; }
    *p = 0x46;
}
