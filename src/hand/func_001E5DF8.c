typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct P {
    char pad[0xE0];
    int fE0;
    int nE4;
    int c;
    int *aE;
    float *aF0;
    qword *aF4;
    char pad2[0x140 - 0xF8];
    qword *a140;
    qword *a144;
};
void LoadLoxBaseFromBrx(struct P *, void *);
int S8Read(void *) asm("S8Read__18CBinaryInputStream");
int U16Read(void *) asm("U16Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct MSG *);
void Read__18CBinaryInputStreamiPv(void *, int, void *);
void ReadVector__18CBinaryInputStreamP6VECTOR(void *, qword *);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(struct P *, void *);
void RecalcCrv__FP3CRV(struct P *);
// name: SafeHouse port (LoadPathFromBrx)
void LoadPathFromBrx__FP2LOP18CBinaryInputStream(struct P *p, void *pbis)
{
    struct MSG msg;
    int i;
    LoadLoxBaseFromBrx(p, pbis);
    p->fE0 = S8Read(pbis);
    p->nE4 = S8Read(pbis);
    p->c = U16Read(pbis);
    msg.cb = p->c * 4;
    msg.nKind = 0x10;
    p->aE = PvAllocSwImpl__Fi(&msg);
    msg.cb = p->c * 4;
    msg.nKind = 0x10;
    p->aF0 = PvAllocSwImpl__Fi(&msg);
    msg.cb = p->c * 16;
    msg.nKind = 0x10;
    p->aF4 = PvAllocSwImpl__Fi(&msg);
    Read__18CBinaryInputStreamiPv(pbis, p->c * 4, p->aE);
    for (i = 0; i < p->c; i++)
        ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &p->aF4[i]);
    if (p->fE0) {
        msg.cb = p->c * 16;
        msg.nKind = 0x10;
        p->a140 = PvAllocSwImpl__Fi(&msg);
        msg.cb = p->c * 16;
        msg.nKind = 0x10;
        p->a144 = PvAllocSwImpl__Fi(&msg);
        for (i = 0; i < p->c; i++)
            ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &p->a140[i]);
        for (i = 0; i < p->c; i++)
            ReadVector__18CBinaryInputStreamP6VECTOR(pbis, &p->a144[i]);
    }
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(p, pbis);
    RecalcCrv__FP3CRV(p);
}
