void *func_0015E938(void *pv, int k, int id, void *ctx);
int func_00132B10(void *p, int cid);
void func_001F6978(void *p, void *q);
void func_001F69F8(void *p, void *q);
void func_00210408(void *pv, int f, int id, void *q, void *pdef, void *ctx)
{
    void *p;
    if (id == -1)
        p = pdef;
    else
        p = func_0015E938(pv, 4, id, ctx);
    if (p && func_00132B10(p, 0x30)) {
        if (f)
            func_001F6978(p, q);
        else
            func_001F69F8(p, q);
    }
}
