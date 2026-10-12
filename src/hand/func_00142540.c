typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x30 - 0x10]; int n30; char pad3[0x40 - 0x34]; qword q40; };
void func_001EECD0(void *p);
struct O *func_00205438(void *p, int n);
void func_00142540(char *p, int a, qword q)
{
    struct O *o;
    struct VTE *e;
    func_001EECD0(p + 0x26C);
    if (a) {
        o = func_00205438(p, 0xC2);
        o->n30 = a;
        o->q40 = q;
        e = &o->vt[8];
        ((void (*)(void *))e->pfn)((char *)o + e->d);
    }
}
