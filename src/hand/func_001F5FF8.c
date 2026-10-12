struct E { int oid; char pad[0x24]; };
struct S { char pad[0xB8]; int c; int pad2; struct E *ae; };
struct E *func_001F5FF8(struct S *p, int oid)
{
    int i;
    for (i = 0; i < p->c; i++) { struct E *pe = &p->ae[i]; if (pe->oid == oid) return pe; }
    return 0;
}
