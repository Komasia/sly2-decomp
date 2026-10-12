typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } MATRIX3;
struct VT { struct { short d; short pad; void (*pfn)(void *, qword); } a[40]; };
struct X { char pad[0x30]; int x30; };
struct O { char pad[0xC]; struct VT *pvt; char pad1[0x194 - 0x10]; int x194; struct X *p198; char pad2[0x1C8 - 0x19C];
    int x1C8; int x1CC; char pad3[0x204 - 0x1D0]; float g204; char pad4[0x210 - 0x208]; qword v210; };
struct MSG { int oid; float g; int k; };
extern "C" void func_001C3E20(struct O *p, int msg, struct MSG *pm);
extern "C" MATRIX3 func_0011B500(qword v, float g);
extern "C" qword func_00204E38(struct O *p, int oid, float g);
extern "C" qword D_002A2DC0;
extern "C" void func_00181060(struct O *p, int msg, struct MSG *pm);
void func_00181060(struct O *p, int msg, struct MSG *pm)
{
    func_001C3E20(p, msg, pm);
    if (msg == 9) {
        if (pm->oid == p->x194 || (p->p198 && pm->oid == p->p198->x30)) {
            switch (pm->k) {
            case 0x15E: {
                MATRIX3 m;
                qword v, r;
                m = func_0011B500(D_002A2DC0, p->g204);
                v = func_00204E38(p, pm->oid, pm->g);
                __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
                    : "=&j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
                p->v210 = r;
                p->pvt->a[35].pfn((char *)p + p->pvt->a[35].d, p->v210);
                break;
            }
            case 0x25:
                p->x1C8 = 1;
                break;
            case 0x26:
                p->x1C8 = 0;
                break;
            case 0x27:
                p->x1CC = 1;
                break;
            case 0x28:
                p->x1CC = 0;
                break;
            }
        }
    }
}
