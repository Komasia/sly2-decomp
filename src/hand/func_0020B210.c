struct S { char pad[0xF80]; int state; int arg; };
void func_00204F78(struct S *p, int a, int b);
void func_0020B210(struct S *p)
{
    switch (p->state) {
    case 0:
        func_00204F78(p, p->arg, 0);
        break;
    case 1:
        func_00204F78(p, p->arg, 0);
        break;
    case 2:
        func_00204F78(p, p->arg, 0);
        break;
    case 3:
        func_00204F78(p, p->arg, 0);
        break;
    }
    p->arg = 0;
    p->state = -1;
}
