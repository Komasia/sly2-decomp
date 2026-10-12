typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct S { char pad[0xC]; struct VTE *vt; void *p10; char pad2[0x50]; float g64; float g68; float g6C; char pad3[0x10]; qword q80; };
extern float D_002BE624, D_002BE628, D_002BE62C;
void func_001EEF70(struct S *p);
qword func_001A62E8(void *p);
void func_00177EF0(struct S *p) {
    struct VTE *e;
    float g;
    func_001EEF70(p);
    p->q80 = func_001A62E8(p->p10);
    g = p->g64 < D_002BE62C ? D_002BE62C : p->g64;
    p->g64 = g;
    p->g6C = D_002BE628 > g ? g : D_002BE628;
    p->g68 = D_002BE624 < g * 0.25f ? D_002BE624 : g * 0.25f;
    e = &p->vt[0xF];
    e->pfn((char *)p + e->d, 0);
}
