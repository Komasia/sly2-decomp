// Complete sprite action dispatcher WIP; sound source argument is a nullable object pointer.
struct O;
struct VT { char pad[0x40]; short d; short pd; int (*kind)(void *); };
struct M { char pad[0xC]; struct VT *vt; };
struct E { char pad[0x14]; struct M *pm; };
struct R { char pad[8]; struct E *ae; };
struct A { int kind; int id; };
struct F { char pad[0x18]; unsigned char count; char pad1[3]; struct A *aa; };
struct S { char pad[4]; struct F *af; char pad1[8]; struct R *r; };
extern char D_003DD040[];
extern "C" struct M *func_001FBB90(int id);
extern "C" void func_001FB2F8(struct M *, struct O *);
extern "C" void func_001FB098(struct M *, float);
extern "C" void func_00258040(struct M **pp, struct M *m);
extern "C" void *func_001FE5F0(void *p,int a,int b);
extern "C" void func_001FE738(void *p);
static inline void Stop(struct M **pp) {
    if (pp && *pp) {
        func_001FB098(*pp,0.0f);
        func_00258040(pp,0);
    }
}
extern "C" void func_00219190(struct S *p,int fi,int i) {
    struct F *f=&p->af[fi];
    int j;
    for (j=0;j<f->count;j++) {
        struct A *a=&f->aa[j];
        switch(a->kind) {
        case 0: {
            struct M *m=func_001FBB90(a->id);
            func_001FB2F8(m,0);
            if(m->vt->kind((char *)m+m->vt->d)==2)
                func_00258040(&p->r->ae[i].pm,m);
            break;
        }
        case 1: {
            struct E *e=(struct E *)(i * sizeof(struct E) + (int)p->r->ae);
            if(e->pm) Stop(&e->pm);
            break;
        }
        case 2: func_001FE5F0(D_003DD040,a->id,0); break;
        case 3: func_001FE738(D_003DD040); break;
        }
    }
}
