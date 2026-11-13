typedef int qword __attribute__((mode(TI)));
struct A { int cb; int align; };
struct E8 { struct V *pv; int x4; };
struct V { qword pos; int c; struct E8 *ae; int pad[2]; };
struct F { struct V *apv[3]; };
struct P { float x, y, z; unsigned short c, d; };
struct S { char pad[0x18]; int x18; char p0[0xE0 - 0x1C]; int cE0; struct V *aE4; int cE8; struct F *aEC; int cF0; struct P *aF4; char p1[0x114 - 0xF8]; int x114; };
struct G { char pad[0x3D70]; int x3D70; char p1[0x45C8 - 0x3D74]; struct S *x45C8; };
extern struct G g_sw;
void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(struct S *p, void *pbis);
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
int U8Read(void *pbis) asm("U8Read__18CBinaryInputStream");
void ReadVector__18CBinaryInputStreamP6VECTOR(void *pbis, struct V *pv);
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
void *PvAllocSwClearImpl__Fi(struct A *pa);
void *PvAllocSwImpl__Fi(struct A *pa);
void func_001C0880(int *p);
// name: SafeHouse port (LoadMeshZoneFromBrx)
void LoadMeshZoneFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *pbis)
{
    struct A a;
    int i, j, k;
    LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(p, pbis);
    p->cE0 = U16Read(pbis);
    a.cb = p->cE0 * 32;
    a.align = 0x10;
    p->aE4 = PvAllocSwClearImpl__Fi(&a);
    p->cE8 = U16Read(pbis);
    a.cb = p->cE8 * 12;
    a.align = 0x10;
    p->aEC = PvAllocSwClearImpl__Fi(&a);
    for (i = 0; i < p->cE0; i++) {
        struct V *pd = &p->aE4[i];
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, pd);
        pd->c = U8Read(pbis);
        a.cb = pd->c * 8 + 8;
        a.align = 0x10;
        pd->ae = PvAllocSwImpl__Fi(&a);
        for (j = 0; j < pd->c; j++) {
            struct E8 *pe = &pd->ae[j];
            pe->pv = &p->aE4[U16Read(pbis)];
        }
    }
    for (k = 0; k < p->cE8; k++) {
        struct V **ppv = p->aEC[k].apv;
        for (i = 0; i < 3; i++)
            *ppv++ = &p->aE4[U16Read(pbis)];
    }
    p->cF0 = U16Read(pbis);
    a.cb = p->cF0 * 16;
    a.align = 0x10;
    p->aF4 = PvAllocSwClearImpl__Fi(&a);
    for (i = 0; i < p->cF0; i++) {
        struct P *pp = &p->aF4[i];
        pp->x = F32Read(pbis);
        pp->y = F32Read(pbis);
        pp->z = F32Read(pbis);
        pp->c = U16Read(pbis);
        pp->d = U16Read(pbis);
    }
    func_001C0880(&p->cE0);
    if (p->x18 == 0x2CA)
        g_sw.x45C8 = p;
    p->x114 = ++g_sw.x3D70;
}
