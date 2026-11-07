typedef struct S { char pad[0x18]; int x18; } S;
extern struct G g_sw;
void *PloFindSwNearest__FP2LO3OIDii(struct G *g, int k, int id, int x);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int k);
void *func_001CB2E0(void *p);
// name: SafeHouse port (PloFind)
void *PloFind__FP3RUNi(S *p, int id)
{
    void *q;
    if (id == -1) {
        q = 0;
    } else {
        q = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, id, p->x18);
        if (q && FIsBasicDerivedFrom__FP5BASIC3CID(q, 6)) q = func_001CB2E0(q);
    }
    return q;
}
