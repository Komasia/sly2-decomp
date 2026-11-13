struct CRef { int tagk; int tag; };
struct CMD { char pad[0x10]; unsigned int c; int a[4]; };
void func_002013D8(struct CRef *pref, void *x, int a, int b, unsigned int *pc, int *pa);
struct CMD *PcmdNew__FP4SCPTii(void *pq, int kind, int b);
void CopyAb(void *pdst, void *psrc, int cb) asm("CopyAb__FPvT0Ui");
void Decref(struct CRef *pref) asm("Decref__4CRef");
void func_001E0310(void *pq, void *x)
{
    int a[8];
    struct CRef ref;
    unsigned int c;
    struct CMD *p;
    func_002013D8(&ref, x, 6, 8, &c, a);
    p = PcmdNew__FP4SCPTii(pq, 3, 0);
    if (c > 4) c = 4;
    {
        unsigned int n = c;
        p->c = n;
        CopyAb(&p->a, a, n * 4);
    }
    Decref(&ref);
}
