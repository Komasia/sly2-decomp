struct AREQ { int cb; int cbAlign; };
struct E { char pad[0x10]; struct E *p10; struct E *p14; int x18; int x1C; };
struct P { char pad[0x4558]; int c; struct E *ae; int n; void *p4564; };
int U16Read(void *pbs) asm("U16Read__18CBinaryInputStream");
void ReadVector4__18CBinaryInputStreamP7VECTOR4(void *pbs, struct E *pe);
int S16Read(void *pbs) asm("S16Read__18CBinaryInputStream");
void *PvAllocSwClearImpl__Fi(struct AREQ *preq);
// name: SafeHouse port (LoadNodesFromBrx)
void LoadNodesFromBrx__FP2SWP18CBinaryInputStream(struct P *p, void *pbs)
{
    struct AREQ req;
    int i;
    int c = U16Read(pbs);
    req.cbAlign = 0x10;
    req.cb = c * sizeof(struct E);
    p->c = c;
    p->ae = (struct E *)PvAllocSwClearImpl__Fi(&req);
    p->n = 0;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        int j;
        ReadVector4__18CBinaryInputStreamP7VECTOR4(pbs, pe);
        j = S16Read(pbs);
        if (j >= 0)
            pe->p10 = &p->ae[j];
        else
            pe->x18 = p->n++;
        j = S16Read(pbs);
        if (j >= 0)
            pe->p14 = &p->ae[j];
        else
            pe->x1C = p->n++;
    }
    req.cbAlign = 0x10;
    req.cb = p->n * sizeof(struct E);
    p->p4564 = PvAllocSwClearImpl__Fi(&req);
}
