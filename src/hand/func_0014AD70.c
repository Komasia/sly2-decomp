struct E { int k; int a, b; };
struct Q { char pad[0x58]; struct E *ae; };
struct P { char pad[0x38]; struct Q *q; int i; int c; };
void SetState__8JOBCHASEi(struct P *p, int n);
// name: SafeHouse port (JOBCHASE::Step)
void Step__8JOBCHASE(struct P *p)
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
        SetState__8JOBCHASEi(p, 1);
        break;
    case 1:
        SetState__8JOBCHASEi(p, 2);
        break;
    }
}
