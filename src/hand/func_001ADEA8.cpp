struct O { char pad[0x58]; int x58; int pad2[2]; int x64; };
struct S { char pad[0x24]; O *po; };
extern "C" int func_001ADEA8(S *p)
{
    O *o = p->po;
    if (!o) return 0;
    if (o->x58 < 2 && o->x64 < 2) return 0; return 1;
}
