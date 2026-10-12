struct S { char pad[0x68]; void *f68; char pad2[0x78 - 0x6C]; int f78; };
extern char D_002DEB30[];
extern char D_002E65E0[];
void func_00164DF0(void *p, int n);
void func_001619A0(void *p, int n, struct S *ps);
void func_00162908(struct S *p);
void func_001ABD98(void *p, int n);
void func_00162F60(struct S *p)
{
    if (!p->f78)
        func_00164DF0(p->f68, 3);
    func_001619A0(D_002DEB30, 0x20, p);
    func_00162908(p);
    if (!p->f78)
        func_001ABD98(D_002E65E0, 0);
}
