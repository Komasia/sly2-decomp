typedef unsigned int uint;
typedef unsigned long ulong;
struct QW { int w[4]; };
struct SEMA {int count,maxCount,initialCount,waitThreads;uint attributes,option;};
struct M2 {float a[8];M2(){}void Identity();};
extern "C" void *func_002333B4(void *,int,int);
inline void M2::Identity(){func_002333B4(this,0,sizeof(*this));a[0]=a[3]=1.0f;}
struct CLOCK {float t,dt,ratio,realRatio,realDt,realT;char pad18[0x24];float frameT,frameDt;ulong tick;};
struct FR {int n0;void *p4;char pad8[0x1C];void *packet;char pad28[8];int flags;};
struct VB {char pad[0xC];unsigned char *m_pb;char pad10[0x10];int m_fCheckCnt;};
struct GF {char pad[0x28];};
extern VB D_002DEA28;
extern GF D_002DEA00;
extern FR *D_002DEA4C;
extern CLOCK D_002DDED0;
extern float *D_002DD314;
extern int D_003D3A3C,D_003D3A40,D_003D3A44,D_002DEDBC,D_002DEB18;
extern uint D_002BE538;
extern int D_002C10A0,D_002C10A4,D_002C10A8,D_002C10AC;
extern float D_002C10B0,D_002C10B4,D_002C10C0[3],D_002BBB60[2];
extern QW D_002DF260[];
extern "C" {
int func_00234A60(int);
int func_00234A40(int);
int func_00234A90(int,SEMA *);
float func_00245000(float);
void func_001C93E0(GF *,M2 *,float);
void func_00160A98(void);
void func_0014D0B8(CLOCK *,int);
void func_00160828(void);
void func_001574B8(VB *);
void func_001576F0(VB *);
void func_002270C8(VB *,int,QW *,int);
}
static inline void Clamp(float *value,const float *bounds){float low=bounds[0],high=bounds[1];if(*value<low)*value=low;else if(high<*value)*value=high;}
extern "C" void func_001C9190(void *)
{
    SEMA status;VB *builder=&D_002DEA28;CLOCK *clock=&D_002DDED0;M2 matrix;
    for(;;){
        func_00234A60(D_003D3A3C);
        D_002DEDBC=0;
        for(;;){ func_0014D0B8(clock,1);func_00160828();D_002DEA4C->packet=builder->m_pb;builder->m_fCheckCnt=1;func_001574B8(builder);func_002270C8(builder,0x25,D_002DF260,0);func_001576F0(builder);func_00234A90(D_003D3A40,&status);if(status.count!=0)break;
            float t=clock->frameT-*D_002DD314;
            float scale=1.0f+D_002C10B0*func_00245000(t*D_002C10B4);
            matrix.Identity();
            matrix.a[0]=D_002C10A0*scale;
            matrix.a[3]=D_002C10A4*scale;
            matrix.a[4]=D_002C10A8;matrix.a[5]=D_002C10AC;
            float alpha=D_002C10C0[0]+t*(D_002C10C0[1]+t*D_002C10C0[2]);
            Clamp(&alpha,D_002BBB60);func_001C93E0(&D_002DEA00,&matrix,alpha);
            func_00160A98();D_002BE538++;
        }
        do{D_002DEA4C->flags&=-2;}while(0);
        func_00160A98();D_002BE538++;
        do {func_00234A90(D_002DEB18,&status);}while(status.count==0);
        func_00234A60(D_003D3A40);
        func_00234A40(D_003D3A44);
    }
}
