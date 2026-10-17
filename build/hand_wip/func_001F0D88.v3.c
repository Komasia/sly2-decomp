/* v3 (Claude agent): pin-free version of v2 (no register asm), aligned 15. Left: target sets a0=p in both branches and shares only the 1F13A8 jal (nop slot). */
struct ANIMATION;
struct T { char pad[0x74]; float f74; };
struct A { struct T *pt; int n4; int n8; };
struct E8 { int n0; int n4; };
struct G { char pad[0x54]; struct E8 *a54; };
struct P { char pad[0x24]; struct G *pg; int n28; int n2C; struct ANIMATION *n30; int n34; int n38; int n3C; struct A *p40; float f44; int n48; };
int func_001F0638(struct P *);
struct A *func_001F0CF0(struct G *, int, int, int);
struct A *func_001F0B80(struct G *, int, int, int, int);
void func_0012F9B8(struct T *, int, float, float, int, struct ANIMATION **);
void func_001333C0(struct ANIMATION *, struct P *);
void func_00130B18(struct ANIMATION *);
void func_001F13A8(struct P *, int, int);
void func_001F0D88(struct P *p, int k)
{
    struct A *pa;
    int nx;
    int fl;
    if (func_001F0638(p)) return;
    {int finished=-1;
    int random=-2;
    goto test;
select:
    if(nx==random){
        pa=func_001F0CF0(p->pg,p->n48,p->n34,0);
        if(pa)p->n3C=(pa->n4!=p->n34)?pa->n4:pa->n8;
    }else{
        p->n3C=nx;
        pa=func_001F0B80(p->pg,p->n48,p->n34,nx,1);
    }
    k=0;
apply:
        p->p40 = pa;
        if (!pa) return;
        fl = 0;
        if (pa->pt) {
            float a, b;
            int f;
            if (pa->n4 == p->n34) {
                p->n38 = pa->n8;
                a = 0.0f;
                b = p->f44;
            } else {
                p->n38 = pa->n4;
                b = -p->f44;
                a = pa->pt->f74;
            }
            f = p->n2C;
            if (k == 1) {
                f |= 2;
                f &= random;
                fl = 1;
                a = pa->pt->f74 - a;
            } else if (pa->pt->f74 == 0.0f) {
                fl = 1;
            }
            func_0012F9B8(pa->pt, p->n28, a, b, f, &p->n30);
        }
        if(!p->n30){
            int old=p->n34;
            int nw=pa->n4;
            if(nw==old)nw=pa->n8;
            p->n34=nw;
            func_001F13A8(p,old,nw);
        }else{
            int old,nw;
            if(!fl){func_001333C0(p->n30,p);return;}
            nw=p->n38;
            old=p->n34;
            p->n34=nw;
            p->n38=finished;
            func_00130B18(p->n30);
            p->n30=0;
            func_001F13A8(p,old,nw);
        }
    if(func_001F0638(p))return;
    if(p->n30)return;
test:
    if(p->n34!=p->n3C){
        pa=func_001F0B80(p->pg,p->n48,p->n34,p->n3C,1);
        goto apply;
    }
    nx=p->pg->a54[p->n34].n4;
    if(nx!=finished)goto select;
}
}
