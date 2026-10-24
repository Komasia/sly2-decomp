// (Claude agent, big10) v7: aligned 30 (v5 42): flags&1 loop has its own counter `int n` (shared i made the reversed counter take s2), loads normal/velocity into plain qword locals first, DotQ lists "j"(b) twice (allocation-only). Left: f21/f22 swap (0.0 vs D_002A8280), case 14 mul operand order, else-loop `slt s7,s6` start test (2 insns).
// (Claude agent, big8) v5: aligned 42 (v4 82). Logic fixes: case 11 also stores upper (cross-jumped tail), func_0011A6B8 only inside the flags&4 block; row before state; flags&4 target via if/else; in-place "+j" dot asms; "memory" clobber on LengthSquared reproduces the p->second reload.
// (Claude agent, big7) v4: 451 words aligned 82 (v3 160). contact/row/i declared once at function scope and reused by every loop (contact is then live across func_0011D448 -> s0, clock pointer kept in a3 via caller-save sq/lq like the target, 0x160 frame).
// (Claude agent, vu_hi6) v3: 423/451 aligned 160 (v2 168). Dot helpers as one vmul/vaddw/vadday/vmaddz asm (the separate volatile vaddw / output-less vadday asms fixed the order).
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
static inline int DotQ(qword a,qword b){qword one;int r;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(a));return r;}
static inline float Dot(qword a,qword b){qword one;float f;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float LengthSquared(qword v){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one): :"memory");__asm__("mtc1 %1,%0":"=f"(f):"r"(v));return f;}
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
    XP *contact;DZ *row;int i;
    DZG group;
    func_001AE478(&frame);
    func_001585D8(&group,contactCount,contacts,objectCount,objects);
    for(i=0;i<contactCount;i++){
        contact=contacts[i];
        row=&group.rows[i];
        DZS *state=&group.states[i];
        state->source=contact;
        state->normal=contact->normal;
        switch(contact->kind){
        case 11:row->kind=1;row->lower=D_002A8280;row->upper=D_002A8284;break;
        case 14:
            if(flags&1){
                row->lower=D_002DDED0.dt*contact->start;
                row->upper=contact->end*D_002DDED0.dt;
                row->kind=contact->start<0.0f;
            }else{row->lower=0.0f;row->upper=D_002A8284;row->kind=0;}
            break;
        default:row->kind=0;row->lower=0.0f;row->upper=D_002A8284;break;
        }
        func_00158668(&group,row,state);
    }
    float maximum;
    if(flags&4){
        maximum=0.0f;
        for(i=0;i<contactCount;i++){
            contact=contacts[i];
            row=&group.rows[i];
            if(row->kind==1)row->target.value=contact->value;else row->target.value=contact->value+1.0f;
            float magnitude=Abs(contact->value);
            if(maximum<magnitude)maximum=magnitude;
        }
        func_00158988(&group,4);
        func_00158E20(&group,maximum+maximum,6.2831855f);
        {int j;for(j=0;j<objectCount;j++){}
        for(j=0;j<objectCount;j++)Callback(objects[j],67);}
        if(flags==4){func_001AE4A0(&frame,2);return;}
        func_0011A6B8(&group);
    }
    maximum=0.0f;
    if(flags&1){
        func_001A7E60(game,contactCount,contacts);
        func_001A7FC0(game,contactCount,contacts);
        int n;for(n=0;n<contactCount;n++){
            contact=contacts[n];
            row=&group.rows[n];
            qword normal=contact->normal.q;qword velocity=contact->velocity.q;row->target.bits=DotQ(velocity,normal);
            float magnitude=LengthSquared(contact->velocity.q);
            if(maximum<magnitude)maximum=magnitude;
        }
    }else{
        for(i=0;i<contactCount;i++){
            contact=contacts[i];
            row=&group.rows[i];
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
        for(i=0;i<objectCount;i++){
            P *p=objects[i];
            if(p->first->kind==2||p->second->kind==2)break;
            BODY *second=p->second;
            MOTION *motion=p->motion;
            int moving=LengthSquared(p->first->velocity.q)>25.0f || Dot(second->velocity.q,p->second->velocity.q)>0.0025000002f || LengthSquared(motion->linear.q)>25.0f || LengthSquared(motion->angular.q)>0.0025000002f;
            if(moving)break;
        }
        if(i>=objectCount){
            for(i=0;i<objectCount;i++)func_001F9C48(objects[i]);
            func_001A7E60(&D_003DD490,contactCount,contacts);
            func_001A7FC0(&D_003DD490,contactCount,contacts);
        }
    }else{
        for(k=0;k<objectCount;k++)Callback(objects[k],66);
    }
    func_001AE4A0(&frame,2);
}
