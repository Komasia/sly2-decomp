struct E { int k; int a, b; };
struct Q { char pad[0x58]; struct E *ae; };
struct P { char pad[0x38]; struct Q *q; int i; int c; };
void func_0014AE38(struct P *p, int n);
void func_0014AD70(struct P *p)
{
    int k;
    if (p->i < p->c) {
        p->i++;
        k = p->q->ae[p->i].k;
    } else {
        k = p->q->ae[p->i].k;
        p->i--;
    }
    switch (k) {
    case 0:
        func_0014AE38(p, 1);
        break;
    case 1:
        func_0014AE38(p, 2);
        break;
    }
}
