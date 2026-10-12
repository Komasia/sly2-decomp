struct B { char pad[8]; short h; char pad2[6]; int p; };
struct S { char pad[8]; struct B *pb; };
int func_00218710(struct S *p)
{
    struct B *b = p->pb;
    if (b->h != 0 && b->p == 0)
        return 1;
    return 0;
}
