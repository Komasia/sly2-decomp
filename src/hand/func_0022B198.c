struct S { int k; char pad[0x50]; void *o; };
int func_002121E8(void *o, int a);
void func_0022B090(struct S *p, int k);
void func_0022B198(struct S *p)
{
    int k = p->k;
    switch (k) {
    case 0: break;
    case 1: if (!func_002121E8(p->o, 0x314)) k = 3; break;
    case 2: if (!func_002121E8(p->o, 0x314)) k = 0; break;
    }
    func_0022B090(p, k);
}
