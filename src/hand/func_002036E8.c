struct G;
extern struct G g_sw;
struct S { char pad[0xEC]; void *o; int n; };
void RequestTaskState__FP4TASKii(void *o, int n, void *p);
char *PloPlayerPo__FP2SW(struct G *pg);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *o, int n);
void SetBinocWindowArgs__FP8BINOCWIN(void *pv);
void func_002036E8(struct S *p, int n)
{
    if (p->o) {
        char *o;
        RequestTaskState__FP4TASKii(p->o, 2, p);
        o = PloPlayerPo__FP2SW(&g_sw);
        if (o && FIsBasicDerivedFrom__FP5BASIC3CID(o, 0x34)) SetBinocWindowArgs__FP8BINOCWIN(o + 0xF24);
    } else p->n = n;
}
