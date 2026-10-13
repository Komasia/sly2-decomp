// Semaphore-driven render thread with pulsing scale and opacity.
#include "vifs.h"
#include "gifs.h"
struct SEMA {int count,maxCount,initialCount,waitThreads;uint attributes,option;};
struct M2 {float a[8];M2(){}void Identity();};
extern "C" void *func_002333B4(void *,int,int);
inline void M2::Identity(){func_002333B4(this,0,sizeof(*this));a[0]=a[3]=1.0f;}
struct CLOCK {float t,dt,ratio,realRatio,realDt,realT;char pad18[0x24];float frameT,frameDt;ulong tick;};
struct FR {int n0;void *p4;char pad8[0x1C];void *packet;char pad28[8];int flags;};
extern VIFS D_002DEA28;
extern GIFS D_002DEA00;
extern FR *D_002DEA4C;
extern CLOCK D_002DDED0;
extern float *D_002DD314;
extern int D_003D3A3C,D_003D3A40,D_003D3A44,D_002DEDBC,D_002DEB18;
extern uint D_002BE538;
extern int D_002C10A0,D_002C10A4,D_002C10A8,D_002C10AC;
extern float D_002C10B0,D_002C10B4,D_002C10C0[3],D_002BBB60[2];
extern QW D_002DF260[];
extern "C" int func_00234A60(int);
extern "C" int func_00234A40(int);
extern "C" int func_00234A90(int,SEMA *);
extern "C" float func_00245000(float);
extern "C" void func_001C93E0(GIFS *,M2 *,float);
extern "C" void func_00160A98(void);
extern "C" void func_0014D0B8(CLOCK *,int);
void OpenFrame(void);
static inline void Clamp(float *value,const float *bounds){float low=bounds[0],high=bounds[1];if(*value<low)*value=low;else if(high<*value)*value=high;}
static inline void BeginFrame(CLOCK*clock,VIFS*builder){func_0014D0B8(clock,1);
            OpenFrame();
            unsigned char *end=builder->m_pb;D_002DEA4C->packet=end;
            builder->m_fCheckCnt=1;
            builder->AddDmaCnt();
            builder->AddVifDirect(0x25,D_002DF260,0);
            builder->EndDmaCnt();}
extern "C" void func_001C9190(void *)
{
    SEMA status;VIFS *builder=&D_002DEA28;CLOCK *clock=&D_002DDED0;M2 matrix;
    for(;;){
        func_00234A60(D_003D3A3C);
        D_002DEDBC=0;
        while(BeginFrame(clock,builder),func_00234A90(D_003D3A40,&status),status.count==0){
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
        D_002DEA4C->flags&=-2;
        func_00160A98();D_002BE538++;
        do {func_00234A90(D_002DEB18,&status);}while(status.count==0);
        func_00234A60(D_003D3A40);
        func_00234A40(D_003D3A44);
    }
}
