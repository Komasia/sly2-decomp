void *PloFindSwNearest__FP2LO3OIDii(void *pv, int k, int id, void *ctx);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
void SetAloSoesByTag__FP3ALOi(void *p, void *q);
void func_001F6B48(void *p, void *q);
void func_002104A0(void *pv, int f, int id, void *q, void *pdef, void *ctx)
{
    void *p;
    if (id == -1)
        p = pdef;
    else
        p = PloFindSwNearest__FP2LO3OIDii(pv, 4, id, ctx);
    if (p && FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x30)) {
        if (f)
            SetAloSoesByTag__FP3ALOi(p, q);
        else
            func_001F6B48(p, q);
    }
}
