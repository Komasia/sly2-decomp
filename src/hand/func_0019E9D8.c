struct S { int pad[3]; int c; float g; };
void func_001E6F10(int, int, float, int);
void func_0019E9D8(struct S *s, int x) { func_001E6F10(s->c, x, s->g, 0); }
