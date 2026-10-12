struct Y { char pad[0x18]; int n; };
struct X { char pad[0x18]; int n; char pad2[0x7C - 0x1C]; struct Y *py; char pad3[0x100 - 0x80]; int f100; int f104; };
int func_00165C28(struct X **ppx1, struct X **ppx2)
{
    struct X *px1 = *ppx1;
    struct X *px2 = *ppx2;
    int n1, n2;
    if (px1->f104 != px2->f104) return px1->f104 - px2->f104;
    n1 = px1->py ? px1->py->n : -1;
    n2 = px2->py ? px2->py->n : -1;
    if (n1 != n2) return n1 - n2;
    if (px1->f100 != px2->f100) return px1->f100 - px2->f100;
    return px1->n - px2->n;
}
