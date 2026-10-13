// Prepare contact limits and construct a horizontal response contact.
typedef int qword __attribute__((mode(TI)));
union VECTOR {qword q;float f[4];};
struct XP;
struct ENDPOINT {void *shape,*owner,*object,*lo;union VECTOR position,local;int pad[4];};
struct XP {struct ENDPOINT endpoints[2];union VECTOR normal;float distance,friction,response;int kind;float lower,upper;int tag;struct XP *next;};
struct STATE {char pad[0xD0];float mass;};
struct P {char padE8[0xE8];struct STATE *state;char padEC[0x16C];void *mesh;};
extern char D_003DD490[];
extern qword D_002A2DA0;
extern float D_002C3C60[],D_002C3C90;
void func_001F4FB0(void);
void func_001A7C18(void *,void *,void *,qword,qword,int,int,int,struct XP **,float);
static __inline__ qword Scale(qword a,float f,union VECTOR *scalar){qword k;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(f));scalar->q=k;__asm__("vmulx.xyzw %0,%0,%1x":"+j"(a):"j"(k));return a;}
static __inline__ void Normal(union VECTOR *v,qword fallback){qword a=v->q,one;register qword d __asm__("vf1");float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));if(len<0.0001f){d=fallback;}else{__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(d):"j"(d),"j"(a));}v->q=d;}
static __inline__ void Store(union VECTOR *p,qword q){__asm__("sqc2 %1,%0":"=m"(p->q):"j"(q));}
static __inline__ qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static __inline__ qword Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static __inline__ float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static __inline__ qword AddScaled(qword a,qword b,qword bits,union VECTOR *scalar){qword k;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(bits));scalar->q=k;__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k));return a;}
void func_00204250(struct P *p,struct XP *x,int side)
{
    union VECTOR direction,difference,point,scalar;
    float sign,separation;qword dot,diff;
    const union VECTOR *otherPosition;
    int kind;
    func_001F4FB0();
    kind=x->kind;x->friction=0.0f;x->response=0.0f;
    if(kind==14){
        if(x->normal.f[2]>0.7f){
            x->friction=D_002C3C90;
            x->lower=p->state->mass*-4500.0f;
            x->upper=p->state->mass*9000.0f;
        }else x->upper=p->state->mass*9000.0f;
        return;
    }
    if(kind!=3){
        if(side!=1)return;
        if(kind!=side && kind!=4 && kind!=5 && kind!=6)return;
    }
    sign=D_002C3C60[side];
    if(sign*x->normal.f[2]>0.0f){
    direction.q=Scale(x->normal.q,sign,&scalar);
    direction.f[2]=0.0f;
    Normal(&direction,D_002A2DA0);
    otherPosition=&x->endpoints[1-side].position;
    diff=Sub(x->endpoints[side].position.q,otherPosition->q);Store(&difference,diff);
    dot=Dot(diff,direction.q);
    point.q=AddScaled(otherPosition->q,direction.q,dot,&scalar);
    separation=X(dot);
    func_001A7C18(D_003DD490,p->mesh,x->endpoints[1-side].shape,point.q,direction.q,10,0,0,&x->next,separation);
    }
}
