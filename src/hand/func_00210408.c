void *func_0015E938(void *pv, int k, int id, void *ctx);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
void ShowAloGlobs__FP3ALOi(void *p, void *q);
void func_001F69F8(void *p, void *q);
void func_00210408(void *pv, int f, int id, void *q, void *pdef, void *ctx)
{
    void *p;
    if (id == -1)
        p = pdef;
    else
        p = func_0015E938(pv, 4, id, ctx);
    if (p && FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x30)) {
        if (f)
            ShowAloGlobs__FP3ALOi(p, q);
        else
            func_001F69F8(p, q);
    }
}
