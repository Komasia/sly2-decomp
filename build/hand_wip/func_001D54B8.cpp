extern "C" {void func_00129EC8(void*);void func_001291A8(void*,const void*);}
struct CRef {int tagk,tag;CRef(bool f){tagk=0x17;tag=f;}CRef(const CRef&r){func_001291A8(this,&r);}~CRef(){func_00129EC8(this);}};
extern "C" CRef func_00258200(void*,const CRef&,void*);
extern char D_003D4A60[];extern void *D_003E0FD8;extern int D_002C2D8C;
static inline void SetPv(void*pv,const CRef&r) {CRef arg(r);const CRef &ret=func_00258200(pv,arg,D_003D4A60);}
static inline void SetPvCtx(void*pv,const CRef&r,void*) {CRef arg(r);const CRef &ret=func_00258200(pv,arg,D_003D4A60);}
extern "C" void func_001D54B8(void);
void func_001D54B8(void) {
 switch(D_002C2D8C) {
 case 1: break;
 case 2: {CRef r(false);SetPvCtx(D_003E0FD8,r,D_003D4A60);break;}
 case 3: {CRef r(true);SetPvCtx(D_003E0FD8,r,D_003D4A60);break;}
 }
}
