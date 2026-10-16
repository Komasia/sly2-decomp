typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct XP;
struct VT {short delta,unused;void (*function)(void *);};
struct BODY {char pad0[0x98];short kind;char pad9A[0x16];U velocity;};
struct MOTION {char pad0[0x60];U linear,angular;};
struct P {char pad0[0xC];VT *vtable;char pad10[0x48];BODY *first,*second;char pad60[0x88];MOTION *motion;};
struct XP {char pad0[0x80];U normal;float value;int unused94;float elasticity;int kind;float start,end;int index;int unusedAC;U velocity;};
struct DLE {void *next,*previous;};
struct DL {void *first,*last;int offset;};
union FLOAT {float value;int bits;};
struct DZ {int kind;float lower,upper,value;FLOAT target;int unused14;float *coefficients;int flags;DLE link;};
struct DZS {char pad0[0x40];U normal;XP *source;float *coefficients;char pad58[8];};
struct DZG {int capacity,count;DZ *rows;DL solved,pending,unused,active;int solvedCount;float *matrix,*inverse,*temporary,*results;int contactCount;XP **contacts;int objectCount;P **objects;DZS *states;};
struct FRAME {FRAME(){}~FRAME(){}};
struct CLOCK {float time,dt;};
struct GAME;
extern CLOCK D_002DDED0;
extern GAME D_003DD490;
extern const float D_002A8280,D_002A8284;
extern "C" {
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *,int);
DZG *func_001585D8(DZG *,int,XP **,int,P **);
void func_00158668(DZG *,DZ *,DZS *);
void func_00158988(DZG *,int);
void func_00158E20(DZG *,float,float);
void func_0011A6B8(DZG *);
void func_001A7E60(GAME *,int,XP **);
void func_001A7FC0(GAME *,int,XP **);
float func_0011D448(float,float);
void func_00158B20(DZG *,int);
void func_001F9C48(P *);
}
static inline qword DotQ(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y": : "j"(r));__asm__("vmaddz.x %0,%1,%0z":"+j"(r):"j"(one));return r;}
static inline int DotBits(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y": : "j"(r));__asm__("vmaddz.x %0,%1,%0z":"+j"(r):"j"(one));return (int)r;}
static inline float Dot(qword a,qword b){qword r,one;float f;__asm__("vmul.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y": : "j"(r));__asm__("vmaddz.x %0,%1,%0z":"+j"(r):"j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(r));return f;}
static inline float LengthSquared(qword v){qword one;float f;__asm__("vmul.xyz %0,%0,%0":"+j"(v));__asm__ __volatile__("vaddw.x %0,$vf0,$vf0w":"=j"(one));__asm__("vadday.x ACC,%0,%0y": : "j"(v));__asm__("vmaddz.x %0,%1,%0z":"+j"(v):"j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
static inline float Sqrt(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline void Callback(P *p,int slot){VT *vt=p->vtable;vt[slot].function((char *)p+vt[slot].delta);}
static inline int HasMotion(P *p){
    BODY *second=p->second;
    if(p->first->kind==2||second->kind==2)return 1;
    return LengthSquared(p->first->velocity.q)>25.0f || Dot(second->velocity.q,p->second->velocity.q)>0.0025000002f || LengthSquared(p->motion->linear.q)>25.0f || LengthSquared(p->motion->angular.q)>0.0025000002f;
}
extern "C" void func_001F9410(GAME *game,int flags,int objectCount,P **objects,int contactCount,XP **contacts)
{
    FRAME frame;
    DZG group;
    func_001AE478(&frame);
    func_001585D8(&group,contactCount,contacts,objectCount,objects);
    for(int i=0;i<contactCount;i++){
        XP *contact=contacts[i];
        DZS *state=&group.states[i];
        DZ *row=&group.rows[i];
        state->source=contact;
        state->normal=contact->normal;
        switch(contact->kind){
        case 11:row->kind=1;row->lower=D_002A8280;break;
        case 14:
            if(flags&1){
                row->lower=contact->start*D_002DDED0.dt;
                row->upper=contact->end*D_002DDED0.dt;
                int isNegative=0;
                if(contact->start<0.0f)isNegative=1;
                row->kind=isNegative;
            }else{row->lower=0.0f;row->upper=D_002A8284;row->kind=0;}
            break;
        default:row->kind=0;row->lower=0.0f;row->upper=D_002A8284;break;
        }
        func_00158668(&group,row,state);
    }
    float maximum;
    if(flags&4){
        maximum=0.0f;
        for(int i=0;i<contactCount;i++){
            XP *contact=contacts[i];
            DZ *row=&group.rows[i];
            row->target.value=row->kind==1?contact->value:contact->value+1.0f;
            float magnitude=Abs(contact->value);
            if(maximum<magnitude)maximum=magnitude;
        }
        func_00158988(&group,4);
        func_00158E20(&group,maximum+maximum,6.2831855f);
        {int j;for(j=0;j<objectCount;j++){}
        for(j=0;j<objectCount;j++)Callback(objects[j],67);}
        if(flags==4){func_001AE4A0(&frame,2);return;}
    }
    func_0011A6B8(&group);
    maximum=0.0f;
    if(flags&1){
        func_001A7E60(game,contactCount,contacts);
        func_001A7FC0(game,contactCount,contacts);
        for(int i=0;i<contactCount;i++){
            XP *contact=contacts[i];
            DZ *row=&group.rows[i];
            row->target.bits=DotQ(contact->velocity.q,contact->normal.q);
            float magnitude=LengthSquared(contact->velocity.q);
            if(maximum<magnitude)maximum=magnitude;
        }
    }else{
        for(int i=0;i<contactCount;i++){
            XP *contact=contacts[i];
            DZ *row=&group.rows[i];
            float factor=1.0f+contact->elasticity*func_0011D448(0.9f,1.1f);
            row->target.value=Dot(contact->velocity.q,contact->normal.q)*factor;
            float magnitude=LengthSquared(contact->velocity.q);
            if(maximum<magnitude)maximum=magnitude;
        }
    }
    func_00158B20(&group,flags);
    float magnitude=Sqrt(maximum);
    func_00158E20(&group,magnitude+magnitude,50.0f);
    int k;for(k=0;k<objectCount;k++){}
    if(flags&1){
        for(k=0;k<objectCount;k++)Callback(objects[k],65);
        int i;
        for(i=0;i<objectCount;i++){
            P *p=objects[i];
            if(p->first->kind==2||p->second->kind==2)break;
            BODY *second=p->second;
            MOTION *motion=p->motion;
            int moving=LengthSquared(p->first->velocity.q)>25.0f || Dot(second->velocity.q,p->second->velocity.q)>0.0025000002f || LengthSquared(motion->linear.q)>25.0f || LengthSquared(motion->angular.q)>0.0025000002f;
            if(moving)break;
        }
        if(i>=objectCount){
            for(int i=0;i<objectCount;i++)func_001F9C48(objects[i]);
            func_001A7E60(&D_003DD490,contactCount,contacts);
            func_001A7FC0(&D_003DD490,contactCount,contacts);
        }
    }else{
        for(k=0;k<objectCount;k++)Callback(objects[k],66);
    }
    func_001AE4A0(&frame,2);
}
