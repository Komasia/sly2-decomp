typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef struct SO { char pad[0xC]; VTE *vt; } SO;
typedef struct I { int k; int v; } I;
typedef struct E { int id; int n; int c; I *a; } E;
typedef struct P {
    char pad0[0x158];
    int x158;
    int i;
    int c;
    E *ae;
} P;
extern char D_003DD490[];
SO *func_0015E938(void *g, int k, int v, P *p);
void func_001F6978(P *p, int v);
void func_001F69F8(P *p, int v);
void func_001F6AC8(P *p, int v);
void func_001F6B48(P *p, int v);

void func_001BAF18(P *p, int id)
{
    int iTarget = p->i;
    int cur, j, k;

    if (id == 0x609) {
        iTarget = 0;
    } else if (id == 0x60A) {
        iTarget = p->c;
    } else if (id != -1) {
        for (j = 0; j < p->c; j++) {
            if (p->ae[j].id == id) {
                iTarget = j;
                break;
            }
        }
    }
    if (p->i == iTarget) return;
    cur = p->i;
    if (p->i < iTarget) {
        do {
            E *pe;
            p->i = cur + 1;
            pe = &p->ae[cur];
            for (k = 0; k < pe->c; k++) {
                I *pi = &pe->a[k];
                SO *ps = 0;
                if ((0xC3 >> pi->k) & 1) {
                    ps = func_0015E938(D_003DD490, 1, pi->v, p);
                    if (!ps) continue;
                }
                switch ((unsigned int)pi->k) {
                case 0:
                    ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
                    break;
                case 1:
                    ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
                    break;
                case 2:
                    func_001F6978(p, pi->v);
                    break;
                case 3:
                    func_001F69F8(p, pi->v);
                    break;
                case 4:
                    func_001F6AC8(p, pi->v);
                    break;
                case 5:
                    func_001F6B48(p, pi->v);
                    break;
                }
            }
            cur = p->i;
        } while (cur < iTarget);
        p->x158 = 0;
    } else if (iTarget < p->i) {
        int j2 = p->i;
        do {
            E *pe;
            p->i = j2 - 1;
            pe = &p->ae[p->i];
            k = pe->c;
            while (k-- > 0) {
                I *pi = &pe->a[k];
                SO *ps = 0;
                if ((0xC3 >> pi->k) & 1) {
                    ps = func_0015E938(D_003DD490, 1, pi->v, p);
                    if (!ps) continue;
                }
                switch ((unsigned int)pi->k) {
                case 0:
                    ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
                    break;
                case 1:
                    ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
                    break;
                case 2:
                    func_001F69F8(p, pi->v);
                    break;
                case 3:
                    func_001F6978(p, pi->v);
                    break;
                case 4:
                    func_001F6B48(p, pi->v);
                    break;
                case 5:
                    func_001F6AC8(p, pi->v);
                    break;
                }
            }
            j2 = p->i;
        } while (iTarget < j2);
        p->x158 = 0;
    } else {
        p->x158 = 0;
    }
}
