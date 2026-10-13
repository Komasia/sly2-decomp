// WIP:38/121 differences; first CRef slots0/10/20 versus10/20/30 and frameD0 versusE0.
extern "C" {void*func_001291A8(void*,const void*);void func_00129EC8(void*);}
struct CRef{
 int tag;
 union {int n;float g;};
 CRef(float x){tag=0x16;g=x;}
 CRef(const CRef&r){func_001291A8(this,&r);}
 ~CRef(){func_00129EC8(this);}
};
struct OPT{int kind,value;};
struct H{char pad[0x9C];float start,end,elapsed;};
struct G{char pad[0x3B0C];H*object;char pad10[0xC];OPT*primary;char pad20[0x38];OPT*options[9];};
struct CLOCK{float time,dt;};
extern G D_003DD490;
extern CLOCK D_002DDED0;
extern int D_002E0C20;
extern char D_003D4A60[],D_002DE578[];
extern "C" CRef func_002581C0(OPT*,void*);
extern "C" CRef func_00258200(OPT*,const CRef&,void*);
extern "C" int func_00210AE0();
extern "C" void func_00154D88(void*,float);
static inline float GetFloat(OPT*p,void*context){const CRef&r=func_002581C0(p,context);return r.g;}
static inline void SetPv(OPT*p,const CRef&r,void*context){CRef arg(r);const CRef&ret=func_00258200(p,arg,context);}
static inline void SetFloat(OPT*p,float x,void*context){CRef r(x);SetPv(p,r,context);}
extern "C" void func_00161478(){
 if(!D_003DD490.primary)return;
 float x=GetFloat(D_003DD490.primary,D_003D4A60);
 {CRef r(x+D_002DDED0.dt);SetPv(D_003DD490.primary,r,D_003D4A60);}
 unsigned int i=func_00210AE0();
 if(i<9){
  OPT*p=D_003DD490.options[i];
  if(p){float g=GetFloat(p,D_003D4A60);SetFloat(p,g+D_002DDED0.dt,D_003D4A60);}
 }
 H*p=D_003DD490.object;
 if(p&&(float)D_002E0C20<10.0f){
  p->elapsed+=D_002DDED0.dt;
  if(p->start<p->elapsed)func_00154D88(D_002DE578,D_002DDED0.dt/(p->end-p->start));
 }
}
