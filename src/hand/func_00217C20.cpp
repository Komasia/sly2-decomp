struct T { char pad[8]; short h8; };
struct S { char pad[8]; T *pt; char padc[0x1C]; int x28; };
struct RGBA { unsigned int u; RGBA(unsigned int x) { u = x; } } __attribute__((aligned(16)));
extern "C" char D_002A3A10[];
extern "C" void func_00218638(S *p, int i);
extern "C" void func_00217D98(S *p, int i, int z, void *q, float f, const RGBA &c0, const RGBA &c1);
extern "C" void func_00217C20(S *p, int i)
{
    if (p->x28) {
        if (p->pt->h8 >= 0)
            func_00218638(p, i);
        RGBA c0(0x7F7F7F7F), c1(0xFFFFFFFF);
        func_00217D98(p, i, 0, D_002A3A10, 0.0f, c0, c1);
    }
}
