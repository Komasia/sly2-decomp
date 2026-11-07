struct R { int id; int res; int x; };
struct E { int a; struct R ar[3]; };
struct S { char pad[0x2C4]; int c; struct E a[8]; };
int PloDanceAseg__FP2LO3OIDiiiii(struct S *p, int id);
// name: SafeHouse port (InitDancer)
void InitDancer__FP2LO(struct S *p)
{
    int i, j;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->a[i];
        for (j = 0; j < 3; j++) {
            if (pe->ar[j].id != -1)
                pe->ar[j].res = PloDanceAseg__FP2LO3OIDiiiii(p, pe->ar[j].id);
        }
    }
}
