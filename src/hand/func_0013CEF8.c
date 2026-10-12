struct G { char pad[0x463c]; int c; };
extern struct G D_003DD490;
struct S { char pad[0x180]; int id; };
void func_00183F50(struct S *);
void func_0013CEF8(struct S *p) { func_00183F50(p); p->id = D_003DD490.c++; }
