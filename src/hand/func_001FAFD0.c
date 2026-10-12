extern char D_002D9D00[];
struct S { int a; int b; int c; void *vt; float g10; char pad[0x1C]; float g30; float g34; char pad2[0xC]; float g44; };
struct S *func_001FAFD0(struct S *p)
{
    p->vt = D_002D9D00;
    p->a = 0; //P
    p->b = 0; //P
    p->g10 = 1.0f; //P
    p->g44 = 1.0f; //P
    p->g30 = 300.0f; //P
    p->g34 = 3000.0f; //P
    return p;
}
