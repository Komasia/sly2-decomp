// WIP 34 diffs: -1 constant gets CSE'd into $s3 across calls (target re-materializes -1 for each compare);
// with the first compare changed to -2 everything else matches.
typedef int qword __attribute__((mode(TI)));
struct O { char pad[0x2DC]; int x2DC; };
struct S { char pad[0xE0]; struct O *pE0; char pad1[0x108 - 0xE4]; void *p108; char pad2[0x124 - 0x10C]; int x124; char pad3[0x13C - 0x128]; int x13C; };
struct G;
extern struct G D_003DD490;
extern int D_002DE240;
struct O *func_001C4A48(struct G *pg);
void func_00221178(struct S *p, int k);
qword func_001A62E8(struct O *po);
qword func_001A6F00(int a, struct S *p, qword q);
int func_00118FB0(void *p, int n, qword v);
int func_00132B10(struct O *po, int n);
void func_00221298(struct S *p)
{
    struct O *po = func_001C4A48(&D_003DD490);
    int f;
    if (!po) return;
    if (po != p->pE0) func_00221178(p, 0);
    p->pE0 = po;
    f = p->x13C;
    if (f == -1) {
        f = func_00118FB0(p->p108, 0x7FFFFFFF, func_001A6F00(0, p, func_001A62E8(po))) != 0;
    }
    if (p->x124) goto set;
    if (!func_00132B10(po, 0x34)) goto set;
    if (po->x2DC == -1) goto set;
    if (D_002DE240) goto set;
    if (p->x13C == -1) return;
set:
    func_00221178(p, f);
}
