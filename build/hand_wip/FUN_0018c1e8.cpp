struct S { int x0; int x4; char pad[0x2C]; int x34; int x38; int x3C; };
struct K;
extern "C" void func_00258248(K *k);
extern "C" int func_0014B670(K *k);
struct K { int a; int b; int c; char pad[0x104];
  K() { c = 2; func_00258248(this); }
  bool FSet(S *p) { if (!p) return false; a = (p->x0 ^ p->x34) + 0xCA0; b = p->x4 ^ p->x3C; c = 2; return b != 0; }
};
extern "C" int FUN_0018c1e8(S *p)
{
    K k;
    if (!k.FSet(p)) return 0; return func_0014B670(&k);
}
