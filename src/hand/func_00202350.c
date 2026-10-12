struct S { char pad[0x10]; long fl; char pad2[0x58]; int n; };
int func_00202350(int a, struct S *p) { int r = 0; if (!(p->fl & 0x1000000000000L)) r = p->n > 0; return r; }
