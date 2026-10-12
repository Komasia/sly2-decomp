struct E { char pad[7]; unsigned char c; unsigned char *pb; char padc[0x14]; };
struct S { int x0; struct E *ae; char pad8[8]; void *x10; };
void func_00218748(void *p, int k);
void func_002190F8(struct S *p, int i, int k)
{
    struct E *e = &p->ae[i];
    int j;
    for (j = 0; j < e->c; j++) {
        if (e->pb[j] == 7)
            func_00218748(p->x10, k);
    }
}
