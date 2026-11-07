struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; char pad[0x58 - 0x10]; struct O *pNext; };
struct S { int a[3]; struct VTE *vt; char pad[0xE0 - 0x10]; unsigned int c; struct O *ao[8]; };
extern struct O *D_003E148C;
void UpdateLo__FP2LO(struct S *p);
void func_00156DE0(struct S *p, int f);
int FListenerHearsNoise__FP2LOP5NOISE(struct S *p, struct O *o);
// name: SafeHouse port (UpdateNoiseListener)
void UpdateNoiseListener__FP2LO(struct S *p)
{
    struct O *o;
    UpdateLo__FP2LO(p);
    func_00156DE0(p, 0);
    for (o = D_003E148C; o; o = o->pNext) {
        int i;
        for (i = 0; i < (int)p->c; i++)
            if (o == p->ao[i])
                break;
        if (i < (int)p->c)
            continue;
        if (!FListenerHearsNoise__FP2LOP5NOISE(p, o))
            continue;
        if (p->c < 8) {
            struct VTE *e = &o->vt[1];
            e->pfn((char *)o + e->d);
            p->ao[p->c++] = o;
            e = &p->vt[3];
            e->pfn((char *)p + e->d, 5, 0, 0, 0, 0);
        }
        return;
    }
}
