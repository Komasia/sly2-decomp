struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct P { char pad[0xC]; struct VTE *vt; char pad2[0x1030 - 0x10]; char m1030[4]; char m1034[4]; };
extern char g_sw[];
void EndActorScriptAnim__FP5ACTOR(struct P *p);
void *PloFindSwNearest__FP2LO3OIDii(void *g, int k, int oid, struct P *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *o, int n);
void ClearSmaHandle__FPP3SMA(void *p);
void func_001305B8(void *o, struct P *p, int a, void *b, float f, float g);
void RetractAsegaPp__FPP5ASEGA(void *p);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *o, struct P *p, int n, int a, void *b);
// name: SafeHouse port (PlayActorScriptAnim)
void PlayActorScriptAnim__FP2LOiii(struct P *p, int oid, int a, int b)
{
    void *o;
    if (oid == -1) {
        EndActorScriptAnim__FP5ACTOR(p);
        return;
    }
    o = PloFindSwNearest__FP2LO3OIDii(g_sw, 1, oid, p);
    if (!o) return;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x6D)) {
        p->vt[88].pfn((char *)p + p->vt[88].d, b);
        ClearSmaHandle__FPP3SMA(p->m1034);
        func_001305B8(o, p, a, p->m1030, 0.0f, 1.0f);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x6F)) {
        p->vt[88].pfn((char *)p + p->vt[88].d, b);
        RetractAsegaPp__FPP5ASEGA(p->m1030);
        ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(o, p, -1, a, p->m1034);
    }
}
