struct EYES { char pad[0x64]; int n64; char pad2[0x74-0x68]; float g74; float g78; };
void func_001EE100(struct EYES *p, int eyess);
void func_001EDA68(struct EYES *p, int iframe);
void func_001EE3B0(struct EYES *p, float g)
{
    p->g78 = g;
    if (g >= 1.0f) {
        func_001EE100(p, 2);
    } else {
        p->n64 = -1;
        func_001EE100(p, 0);
    }
    func_001EDA68(p, (int)p->g74);
}
