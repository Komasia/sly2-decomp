struct G;
extern struct G g_sw;
struct Z { char pad[0xF8]; int xF8; };
struct Y { char pad[0x74]; int c; struct Z *a[1]; };
struct X { char pad[0xF38]; struct Y *py; };
struct X *PloPlayerPo__FP2SW(struct G *g);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int cid);
char *func_0013E368(struct G *g, int id);
void s1_strcpy(char *dst, char *src) asm("strcpy");
void func_002111F0(char *dst, int i)
{
    struct G *g = &g_sw;
    struct X *p = PloPlayerPo__FP2SW(g);
    if (p && FIsBasicDerivedFrom__FP5BASIC3CID(p, 0x34)) {
        struct Y *y = p->py;
        if (y && i < y->c)
            s1_strcpy(dst, func_0013E368(g, y->a[i]->xF8));
    }
}
