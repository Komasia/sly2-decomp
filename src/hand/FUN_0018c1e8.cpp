/* FUN_0018c1e8 (0x1AB750): the size of a disc file given by its key record (the sector and size words stored XORed
 * with +0x34 / +0x3C, the sector offset by 0xCA0): a file key (CFileLocation-style, 0x110 bytes) is made from it and
 * its size returned (0x14B670); 0 for no key or an empty file. */
struct S { int x0; int x4; char pad[0x2C]; int x34; int x38; int x3C; };
struct K;
extern "C" void func_00258248(K *k);
extern "C" int func_0014B670(K *k);
struct K { int a; int b; int c; char pad[0x104];
  K() { c = 2; func_00258248(this); }
  bool FSet(S *p) { if (!p) return false; b = p->x4 ^ p->x3C; a = (p->x0 ^ p->x34) + 0xCA0; c = 2; return b != 0; }
};
extern "C" int FUN_0018c1e8(S *p)
{ K k; bool f = k.FSet(p); if (f) return func_0014B670(&k); else return 0; }
