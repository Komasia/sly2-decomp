struct E { int a[2]; char b[0x58]; };
struct S { char pad[0x190]; int c; int pad2[3]; struct E ae[8]; };
void func_001F5988(struct S *p, void *q);
void func_001F4DA8(struct S *p, void *q, void *pe);
void func_001D3F30(struct S *p, void *q) {
    int i;
    func_001F5988(p, q);
    for (i = 0; i < p->c; i++) func_001F4DA8(p, q, p->ae[i].b);
}
