typedef int qword __attribute__((mode(TI)));
struct O;
struct T;
struct C;
struct R { char pad[0x9C]; int kind; };
struct VT { short delta, pad; void (*fn)(struct C *, float, qword *, float, void *); };
class C { public: virtual void v1(); virtual void v2(); virtual void Evaluate(float,qword *,float,void *); };
struct E { int id; struct C *curve; };
struct T {
    char pad[0x5C]; int count; struct E *entries;
    char pad64[0x10]; float duration;
    char pad78[0x58]; char *data;
};
struct B { int id; struct T *src; void *value; int pad; qword velocity, start, end; };
struct P { struct O *owner; struct T *table; int pad[2]; struct B entries[2]; };
struct OID { int id, n; };
extern struct OID D_002C3DC0[], D_002C3DC8[], D_002C3DD0[], D_002C3DD8[];
extern "C" void FillBlAmrsg__FiiPviiP3OID(int, int, void *, int, int, struct OID *);
extern "C" void func_00137A30(struct O *, int, int, void *, int, struct OID *, struct OID *, struct T **);
extern "C" struct E *func_0012FF10(struct T *, struct O *, void *, int);
extern "C" void func_0012FE58(struct T *, struct O *, int *, struct O **, struct R **);
extern "C" void func_001384C0(struct T *);
static inline void Evaluate(struct C *c,qword *p,float t,float gain)
{
    c->Evaluate(t,p,gain,0);
}
static inline qword Sub(qword a,qword b)
{
    __asm__("vsub.xyzw %0,%1,%2":"=j"(a):"0"(a),"j"(b));
    return a;
}
static inline qword Divide(qword v,qword scale)
{
    qword r;
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"0"(scale),"j"(v));
    return r;
}
extern "C" void func_0020B868(struct P *p)
{
    if(p->entries[0].src) {
        struct B *base=p->entries,*b;
        unsigned int i; float gain=1.0f;
        FillBlAmrsg__FiiPviiP3OID(0x40,2,base,0x20,2,D_002C3DC0);
        FillBlAmrsg__FiiPviiP3OID(0x40,2,base,0x30,2,D_002C3DC8);
        for(i=0,b=base;i<2;i++,b++) {
            struct T *src=b->src;
            if(src) {
                struct E *e=func_0012FF10(src,p->owner,(void *)1,1);
                struct { float f[4]; } __attribute__((aligned(16))) start,end;
                union { qword q; float f; int i; } scale;
                Evaluate(e->curve,(qword *)&start,0.0f,gain);
                Evaluate(e->curve,(qword *)&end,src->duration,gain);
                __asm__("qmtc2.ni %1,%0":"=j"(scale.q):"r"(*(int *)&src->duration));
                b->velocity=Divide(Sub(*(qword *)&end,*(qword *)&start),scale.q);
            }
        }
        func_00137A30(p->owner,0x40,2,base,2,D_002C3DD8,D_002C3DD0,&p->table);
        {
            int j;
            for(j=0;j<p->table->count;j++) {
                struct E *e=&p->table->entries[j];
                struct B *pos,*neg;
                struct O *owner;
                struct R *r;
                if(e->id<0) { pos=0;neg=(struct B *)e->curve; }
                else { pos=(struct B *)e->curve;neg=0; }
                func_0012FE58(p->table,p->owner,&e->id,&owner,&r);
                switch(r->kind) {
                case 16:case 18:case 20:
                    if(pos)pos->value=p->table->data+0xC;
                    if(neg)neg->value=p->table->data+0xC;
                    break;
                case 17:case 19:case 21:break;
                default:
                    if(pos)pos->value=0;
                    if(neg)neg->value=0;
                    break;
                }
            }
        }
        func_001384C0(p->table);
    }
}
