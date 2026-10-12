struct E { char pad[0x14]; int id; };
struct S { unsigned short c; short pad; struct E *a; char pad8[0x20]; int x28; };
void func_00217C20(struct S *p, int i);
void func_00217BA0(struct S *p, int k)
{
    int i;
    if (p->x28) {
        i = 0;
        if (k != 0x314) {
            for (i = 0; i < p->c; i++)
                if (k == p->a[i].id) break;
            if (i >= p->c) i = 0;
        }
        func_00217C20(p, i);
    }
}
