struct T { char pad[0x74]; float f74; };
struct A { struct T *pt; int n4; int n8; };
struct E8 { int n0; int n4; };
struct G { char pad[0x54]; struct E8 *a54; };
struct P { char pad[0x24]; struct G *pg; int n28; int n2C; int n30; int n34; int n38; int n3C; struct A *p40; float f44; int n48; };
int func_001F0638(struct P *);
struct A *func_001F0CF0(struct G *, int, int, int);
struct A *func_001F0B80(struct G *, int, int, int, int);
void func_0012F9B8(struct T *, int, int, int *, float, float);
void func_001333C0(int, struct P *);
void func_00130B18(int);
void func_001F13A8(struct P *, int, int);
void func_001F0D88(struct P *p, int k)
{
    struct A *pa;
    int nx;
    int fl;
    if (func_001F0638(p)) return;
    for (;;) {
        if (p->n34 == p->n3C) {
            nx = p->pg->a54[p->n34].n4;
            if (nx == -1) break;
            if (nx == -2) {
                pa = func_001F0CF0(p->pg, p->n48, p->n34, 0);
                k = 0;
                if (pa) {
                    int v = pa->n4;
                    if (v == p->n34) v = pa->n8;
                    p->n3C = v;
                }
            } else {
                p->n3C = nx;
                pa = func_001F0B80(p->pg, p->n48, p->n34, nx, 1);
                k = 0;
            }
        } else {
            pa = func_001F0B80(p->pg, p->n48, p->n34, p->n3C, 1);
        }
        p->p40 = pa;
        if (!pa) return;
        fl = 0;
        if (pa->pt) {
            float a, b;
            int f;
            if (pa->n4 != p->n34) {
                p->n38 = pa->n4;
                b = -p->f44;
                a = pa->pt->f74;
            } else {
                p->n38 = pa->n8;
                a = 0.0f;
                b = p->f44;
            }
            f = p->n2C;
            if (k == 1) {
                f = (f | 2) & ~1;
                fl = 1;
                a = pa->pt->f74 - a;
            } else if (pa->pt->f74 == 0.0f) {
                fl = 1;
            }
            func_0012F9B8(pa->pt, p->n28, f, &p->n30, a, b);
        }
        if (!p->n30) {
            int old = p->n34;
            int v = pa->n4;
            if (v == old) v = pa->n8;
            p->n34 = v;
            func_001F13A8(p, old, v);
        } else {
            int old;
            int nw;
            if (!fl) {
                func_001333C0(p->n30, p);
                return;
            }
            nw = p->n38;
            old = p->n34;
            p->n34 = nw;
            p->n38 = -1;
            func_00130B18(p->n30);
            p->n30 = 0;
            func_001F13A8(p, old, nw);
        }
        if (func_001F0638(p)) return;
        if (p->n30) return;
    }
}
