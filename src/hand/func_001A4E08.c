struct S { int x0; char pad[0x1C0]; int x1c4; };
extern char D_002A3868[], D_002A38A8[];
void func_001A5020(struct S *p, void *b);
void func_001A50F8(struct S *p);
void func_001A5078(struct S *p, void *b, int n, int m);
void func_001A4E80(struct S *p);
void func_001A4E08(struct S *p)
{
    p->x0 = 0;
    p->x1c4 = 0;
    func_001A5020(p, D_002A3868);
    func_001A50F8(p);
    func_001A5078(p, D_002A38A8, 0x189, 1);
    func_001A4E80(p);
}
