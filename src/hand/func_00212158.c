struct S { int x0; int x4; char pad[4]; void *vt; char pad2[0x6C]; int x7c; char pad3[0x4C]; int a[10]; char pad4[8]; char xfc[4]; };
extern char D_002DAF30[];
void func_0011A050(void *p, int n);
struct S *func_00212158(struct S *p)
{
    unsigned int i;
    p->vt = D_002DAF30;
    p->x7c = -1;
    p->x0 = 0;
    p->x4 = 0;
    for (i = 0; i < 10; i++)
        p->a[i] = -1;
    func_0011A050(p->xfc, 0x68);
    return p;
}
