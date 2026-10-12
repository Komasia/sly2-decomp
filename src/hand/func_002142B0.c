struct E { char pad[0x14]; int id; };
struct S { unsigned short c; short pad; struct E *ae; };
int func_002142B0(void *pv, struct S *p, int id)
{
    int i;
    if (id == -1)
        return 0;
    for (i = 0; i < p->c; i++) {
        if (id == p->ae[i].id)
            return 1;
    }
    return 0;
}
