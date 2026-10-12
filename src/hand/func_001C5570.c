struct C { char pad[0x60]; void *p60; };
struct B { char pad[0xEC]; struct C *pc; };
struct Q { int a; struct B *pb; int pad[2]; unsigned long fl; };
int func_00132B10(void *p, int n);
int func_001C5570(void *p, struct Q *q)
{
    void *s;
    /*B*/if (q->fl & (1UL << 48)) return 0; s = q->pb->pc->p60; if (func_00132B10(s, 0x32) || func_00132B10(s, 0x4F)) return 0; return 1;/*E*/
}
