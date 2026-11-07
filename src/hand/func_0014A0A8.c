typedef int qword __attribute__((mode(TI)));
struct E { int a; int oid; void *p; };
struct Q { char pad[0xE8]; int c; char pad2[0xF4 - 0xEC]; qword *aq; };
struct P { char pad[0x54]; int c; struct E *ae; struct Q *q; };
extern char g_sw[];
void PostLoLoad__FP2LO(struct P *p);
struct Q *func_001E94B0(int k, int c);
void *PloFindSwNearest__FP2LO3OIDii(void *p, int k, int oid, void *q);
qword PosOfLo__FP2LO(void *p);
void RecalcCrv__FP3CRV(struct Q *q);
// name: SafeHouse port (PostLoadChasegraph)
void PostLoadChasegraph__FP2LO(struct P *p)
{
    int i;
    PostLoLoad__FP2LO(p);
    p->q = func_001E94B0(0x62C, p->c);
    p->q->c = p->c;
    for (i = 0; i < p->c; i++) {
        struct E *e = &p->ae[i];
        void *o = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, e->oid, p);
        e->p = o;
        if (o) {
            qword *pq = (qword *)((i << 4) + (int)p->q->aq);
            *pq = PosOfLo__FP2LO(o);
        }
    }
    RecalcCrv__FP3CRV(p->q);
}
