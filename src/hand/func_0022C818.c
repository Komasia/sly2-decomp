struct S { char pad[0x80]; int a; float b; int *pa; float *pb; };
void func_0022C818(void *q, struct S *p)
{
    p->b = 1.0f;
    p->a = 0;
    p->pa = &p->a;
    p->pb = &p->b;
}
