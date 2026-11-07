typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { char pad[0x28]; ulong fl; };
struct P { char pad[0xC]; struct VTE *pvt; float f10; char pad1[0x1C - 0x14]; struct O *po; qword v20; char x30[0x14]; float f44; };
void Stop__4CSndf(struct P *, float);
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct O *, int, qword);
void func_001FB778(struct P *, qword, void *, float *, int *);
void SetDirty__4CSndUiUi(struct P *, int, int);
void SetPan__4CSndi(struct P *, int);
// name: SafeHouse port (CSnd::Update3D)
void Update3D__4CSnd(struct P *p)
{
    float f;
    int n;
    float r;
    if (p->po && !((p->po->fl >> 60) & 1)) {
        Stop__4CSndf(p, 0.0f);
        return;
    }
    func_001FB778(p, ConvertPos__FP2LOT0G9VU_VECTOR(p->po, 0, p->v20), p->x30, &f, &n);
    r = p->f10 * f;
    if ((int)(r * 1024.0f) != (int)(p->f44 * 1024.0f)) {
        if (p->f44 == 0.0f) p->pvt[15].pfn((char *)p + p->pvt[15].d, 0);
        else if (r == 0.0f) p->pvt[15].pfn((char *)p + p->pvt[15].d, 1);
        p->f44 = r;
        SetDirty__4CSndUiUi(p, 0x10, 0x10);
    }
    SetPan__4CSndi(p, n);
}
