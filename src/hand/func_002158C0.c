struct L { char pad[0x84]; char *pb; };
struct Q { char pad[0x20]; void *x20; };
struct S { int x0; int k; struct L *pl; int xc; int i; struct Q *x14; };
struct T { char pad[0x58]; int x58; };
void func_00218660(void *p, int a);
void func_001BED18(void *p);
void func_002156B8(struct T *t);
void func_002158C0(struct S *p, struct T *t)
{
    switch (p->k) {
    case 4:
        func_00218660(p->pl->pb + p->i * 0x30, t->x58);
        break;
    case 6:
        if (p->x14) {
            if (p->x14->x20)
                func_001BED18(p->x14->x20);
            p->x14 = 0;
        }
        break;
    }
    func_002156B8(t);
}
