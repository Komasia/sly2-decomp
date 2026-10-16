typedef int qword __attribute__((mode(TI)));
struct O;
struct T;
struct C;
struct R { char pad[0x9C]; int kind; };
struct VT { short delta, pad; void (*fn)(struct C *, float, qword *, float, qword *); };
struct C { VT *vt; };
struct E { int id; struct C *curve; };
struct GROUP { int offset,count; void *items; };
union FLOATWORD { float value; int bits; };
struct T {
    char pad[0x5C]; int count; struct E *entries;
    char pad64[0x10]; union FLOATWORD duration;
    char pad78[0x58]; struct GROUP *data;
};
struct MRSG { float time, delta; };
struct B { float weight; struct T *src; struct GROUP *value; int pad; qword velocity; struct MRSG start[2],end[2]; };
struct P { struct O *owner; struct T *table; int pad[2]; struct B entries[2]; };
struct OID { int id; };
extern struct OID D_002C3DC0[], D_002C3DC8[];
extern int D_002C3DD0[],D_002C3DD8[];
extern "C" void FillBlAmrsg__FiiPviiP3OID(int, int, void *, int, int, struct OID *);
extern "C" void func_00137A30(struct O *, int, int, void *, int, int *, int *, struct T **);
extern "C" struct E *func_0012FF10(struct T *,struct O *,int,int);
extern "C" void func_0012FE58(struct T *, struct O *, int *, struct O **, struct R **);
extern "C" void func_001384C0(struct T *);
static inline void Evaluate(struct C *c,qword *p,float t,float gain)
{
    VT &entry=c->vt[3];
    entry.fn((C*)((char *)c+entry.delta),t,p,gain,0);
}
static inline B *RetainBindings(B *value){
 register B *input asm("$16")=value;
 register B *result asm("$21");
 asm("daddu %0,%1,$zero":"=r"(result):"r"(input));
 return result;
}
extern "C" void func_0020B868(struct P *p)
{
    if(p->entries[0].src) {
        register struct B *initialBase __asm__("$16")=p->entries;
        register struct B *base __asm__("$21");
        register struct B *b __asm__("$18");
        register unsigned int i __asm__("$20");
        register float gain __asm__("$f20");
        FillBlAmrsg__FiiPviiP3OID(0x40,2,initialBase,0x20,2,D_002C3DC0);
        base=RetainBindings(initialBase);
        gain=1.0f;
        i=0;
        FillBlAmrsg__FiiPviiP3OID(0x40,2,initialBase,0x30,2,D_002C3DC8);
        register T **tableOutput __asm__("$22")=&p->table;
        for(b=base;i<2;i++,b++) {
            register struct T *src __asm__("$17")=b->src;
            if(src) {
                register struct E *e __asm__("$16")=func_0012FF10(src,p->owner,1,1);
                struct { float f[4]; } __attribute__((aligned(16))) start,end;
                union { qword q; float f; int i; } scale;
                Evaluate(e->curve,(qword *)&start,0.0f,gain);
                struct C *endCurve=e->curve;
                VT &endEntry=endCurve->vt[3];
                register float endGain __asm__("$f13")=gain;
                endEntry.fn((C*)((char *)endCurve+endEntry.delta),src->duration.value,(qword *)&end,endGain,0);
                register int bits __asm__("$17")=src->duration.bits;
                register qword duration __asm__("vf2");
                register qword last __asm__("vf3");
                register qword first __asm__("vf1");
                register qword difference __asm__("vf3");
                register qword velocity __asm__("vf2");
                __asm__("qmtc2.ni %3,%0\n\tlqc2 %1,%4\n\tlqc2 %2,%5"
                        : "=j"(duration),"=j"(last),"=j"(first)
                        : "r"(bits),"m"(end),"m"(start));
                scale.q=duration;
                __asm__("vsub.xyzw %0,%1,%2":"=j"(difference):"0"(last),"j"(first));
                __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q"
                        : "=j"(velocity) : "0"(scale.q),"j"(difference));
                b->velocity=velocity;
            }
        }
        func_00137A30(p->owner,0x40,2,base,2,D_002C3DD8,D_002C3DD0,tableOutput);
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
                    if(pos)pos->value=&p->table->data[1];
                    if(neg)neg->value=&p->table->data[1];
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
