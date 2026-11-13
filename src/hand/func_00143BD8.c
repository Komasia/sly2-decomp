struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct CRef { int tagk; int tag; };
extern char D_002A4DB0[];
extern int D_003E1084;
void func_001D8A38(struct CRef *r, void *a, void *b, int c);
void Decref(struct CRef *r) asm("Decref__4CRef");
void AkeyReturnBooty__FP5ACTORi(struct O *p, int n);
void GiveActorBooty__FP5ACTORi(struct O *p, int n);
// name: SafeHouse port (PostLoadActorBooty)
void PostLoadActorBooty__FP5ACTOR(struct O *p)
{
    struct CRef r;
    int n;
    struct VTE *e = &p->vt[103];
    func_001D8A38(&r, ((void *(*)(void *))e->pfn)((char *)p + e->d), D_002A4DB0, 0);
    n = r.tag;
    Decref(&r);
    if ((unsigned int)(n + 1) < 2) return;
    if (D_003E1084 & 0x40) AkeyReturnBooty__FP5ACTORi(p, n);
    else GiveActorBooty__FP5ACTORi(p, n);
}
