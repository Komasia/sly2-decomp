typedef int qword __attribute__((mode(TI)));
struct VTE { short d,pad; void (*fn)(void *,int); };
struct POS { char pad[0x70]; qword pos; };
struct SHAPE {
    struct POS *pos; int pad4; float radius; int padC;
    unsigned long flags; char pad18[0xB0-0x18];
};
struct SO { char pad[0xE0]; int count; struct SHAPE *shapes; };
struct S { char pad[0xC]; struct VTE *vt; char pad10[0x1DC-0x10]; float radius; };
struct Q { int enabled,pad4; float radius; struct SO *so; };
extern float D_002C0D7C;
qword func_001A62E8(void *);
int func_001A93C8(qword,struct SHAPE *,int,int,int,int,void *,float);
static inline void Trigger(struct S *p)
{
    struct VTE *m=&p->vt[76];
    m->fn((char *)p+m->d,1);
}
static inline qword ToVu(qword a)
{
    qword b;
    __asm__("qmtc2 %1,%0":"=j"(b):"r"(a));
    return b;
}
static inline qword Sub(qword a,qword b)
{
    qword d;
    __asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));
    return d;
}
static inline float LenSq(qword a)
{
    qword d,one;
    float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));
    __asm__("mtc1 %1,%0":"=f"(f):"r"(d));
    return f;
}
int func_001C5B20(struct S *p,struct Q *q)
{
    char scratch[0x30] __attribute__((aligned(16)));
    qword pos;
    int i;
    float distance,maximum;
    if(!q->enabled||!q->so)return 0;
    pos=ToVu(func_001A62E8(p));
    distance=LenSq(Sub(pos,func_001A62E8(q->so)));
    maximum=D_002C0D7C;
    if(maximum*maximum<distance)return 0;
    if(distance<q->radius*q->radius) {
        Trigger(p);
        return 1;
    }
    for(i=0;i<q->so->count;i++) {
        struct SHAPE *s=&q->so->shapes[i];
        if(s->flags&(1UL<<50))continue;
        if(s->flags&(1UL<<49)) {
            float r=p->radius+s->radius;
            qword here=func_001A62E8(p);
            if(LenSq(Sub(here,s->pos->pos))<r*r) {
                Trigger(p);
                return 1;
            }
        } else {
            qword here=func_001A62E8(p);
            if(func_001A93C8(here,s,0x7FFFFFFF,0,0,1,scratch,p->radius)) {
                Trigger(p);
                return 1;
            }
        }
    }
    return 0;
}
