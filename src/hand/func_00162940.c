struct X { char pad[0x64]; int f64; char pad2[0x84 - 0x68]; struct X *pNext; };
struct S { char pad[0x7C]; int f7c; struct X *pFirst; };
void func_001643B0(struct X *p);
void func_00163460(struct S *p);
void func_00162940(struct S *p)
{
    struct X *px;
    for (px = p->pFirst; px; px = px->pNext) {
        px->f64 = 0;
        func_001643B0(px);
    }
    p->f7c = 0;
    func_00163460(p);
}
