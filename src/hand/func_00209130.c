struct H { int a; void *po; };
struct E { int k; struct H *h; int n8; int nC; };
extern char D_003DD490[];
void func_0020BD88(struct H *h, int arg);
void func_0020C7E0(struct H *h);
void *func_0015E938(void *p, int n, struct H *h, int arg);
int func_00132EA0(void *po);
int func_0012F938(void *po, int n);
struct H *func_0020C010(int cb);
void func_0020BD78(struct H *h);

void func_00209130(struct E *e, int arg)
{
    void *o;
    if (e->k != 2) {
        if (e->k == 3) {
            func_0020C7E0(e->h);
            return;
        }
    } else {
        func_0020BD88(e->h, arg);
        return;
    }
    o = func_0015E938(D_003DD490, 4, e->h, arg);
    if (!o) {
        e->k = -1;
        return;
    }
    switch (func_00132EA0(o)) {
    case 0x6D:
        if (func_0012F938(o, 0x22)) {
            e->k = 2;
            e->h = func_0020C010(0x40);
            func_0020BD78(e->h);
            e->h->po = o;
            func_0020BD88(e->h, arg);
            if (e->nC == -1)
                e->nC = 0;
        } else {
            e->h = o;
            e->k = 0;
        }
        break;
    case 0x6F:
        e->k = 1;
        e->h = o;
        if (e->nC == -1)
            e->nC = 0;
        break;
    default:
        e->k = -1;
        break;
    }
}
