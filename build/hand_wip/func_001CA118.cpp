struct VTE { short d; short pad; void (*pf)(); };
struct LO { char pad[0xC]; struct VTE *vt; char p1[0x3C - 0x10]; struct N *x3C; };
struct N { int id; struct N *parent; char pad8[8]; struct LO *owner; };
struct R { int n; char pad[0x6C - 4]; };
struct G { char pad[0x3F08]; struct R *ar; N *x3F0C; };
struct H {};
extern struct G D_003DD490;
extern "C" struct N *func_001C99D8(N *p, int c, const int *a);
extern "C" int func_001C9950(int id);
extern "C" struct H*func_001AE478(struct H *p);
extern "C" void func_001AE4A0(struct H *p, int n);
extern "C" void func_001CA118(struct LO *p, int key, int f)
{
    register int id __asm__("$20")=key;
    int a[16];
    struct H h;
    struct LO **ap;
    struct N *pn;
    struct N *r;
    int c = 16;
    pn = p->x3C;
    for (; pn && pn->id != -1; pn = pn->parent)
        a[--c] = pn->id;
    c--;
    __asm__("sw %1,%0":"=m"(a[c]):"r"(id));
    r = func_001C99D8(D_003DD490.x3F0C, 16 - c, &a[c]);
    for (pn = p->x3C; pn->id != -1 && pn->owner == p; pn = pn->parent)
        pn->owner = 0;
    for(pn=r;pn->id!=-1;pn=pn->parent){
        struct R*row=&D_003DD490.ar[func_001C9950(pn->id)];
        if(row->n!=1)break;
        if(pn->owner)break;
        pn->owner=p;
    }
    p->x3C = r;
    if (f) {
        int n, i;
        func_001AE478(&h);
        n = ((int (*)(void *, struct LO ***))p->vt[28].pf)((char *)p + p->vt[28].d, &ap);
        for (i = 0; i < n; i++) {
            struct LO *q = ap[i];
            ((void (*)(void *, int, int))q->vt[25].pf)((char *)q + q->vt[25].d, id, 1);
        }
        func_001AE4A0(&h, 2);
    }
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char owner_layout[(sizeof(H)==1 && sizeof(int)==4 && sizeof(void*)==4 && sizeof(VTE)==8 && sizeof(R)==0x6C && OFF(VTE,d)==0 && OFF(VTE,pf)==4 && OFF(LO,vt)==0xC && OFF(LO,x3C)==0x3C && OFF(N,id)==0 && OFF(N,parent)==4 && OFF(N,owner)==0x10 && OFF(G,ar)==0x3F08 && OFF(G,x3F0C)==0x3F0C && OFF(R,n)==0)?1:-1];
