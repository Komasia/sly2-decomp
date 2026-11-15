// DrawVehiclePose (SafeHouse vehicle.cpp, orig 0x1D41F8): at draw time, set each wheel's transform node from its
// suspension height (resting on its best contact) and its rolling/steering rotation, then refresh the world transforms.
// Layouts: VEHICLE / VEHICLEWHEEL (field: SafeHouse port, vehicle.h).
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
union V{qword q;float f[4];};
struct M3{V r[3];};
struct M4{M3 basis;V position;};
struct NODE{M4 matrix,local;char pad80[0x20];NODE*parent;int generation;};
struct CONTACT{char pad[0x90];float height;};
struct WHEEL{int id;NODE*node;CONTACT*contacts;float steerFraction,sideFraction;float tilt,speed,angle,radius;char pad24[12];float x,y;char pad38[0x20];float lowerZ;char pad5C[4];};
struct VEHICLE;
struct VEHICLE{char pad[0xC];VTENT*vt;char pad10[0x50];VEHICLE*space;char pad64[0x12C];int cwheel;char pad194[12];WHEEL awheel[8];char pad4A0[0xB0];float drive;};
#include "clock.h"
struct G{char pad[0x3D58];int generation;};
extern G g_sw;
extern qword g_normalZ,D_002A2DB0;
extern char D_002C21A0[],D_002C21B0[],D_002C21C0[];
extern float D_002C21CC;
extern "C" {
qword ConvertVec(VEHICLE*,VEHICLE*,qword) asm("ConvertVec__FP2LOT0G9VU_VECTOR");
qword PosConvertXfs(VEHICLE*,NODE*,qword) asm("PosConvertXfs__FP2XFT0G9VU_VECTOR");
CONTACT*BestContact(VEHICLE*,WHEEL*) asm("BestContact__FP12VEHICLEWHEELi");
float GSmooth(float,float,float,void*,float*) asm("GSmooth__FfffP3SMPPf");
float RadNormalize(float) asm("RadNormalize__Ff");
M3*BuildRotateMatrixAxis(M3*,qword,float) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
qword*func_00256D18(qword*,qword);
void UpdateAloXfWorlds(VEHICLE*) asm("UpdateAloXfWorlds__FP3ALO");
void RenderSoSelf(VEHICLE*) asm("RenderSoSelf__FP2SOP2CMP2RO");
}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline M3 Rotation(qword axis,float angle) return r{BuildRotateMatrixAxis(&r,axis,angle);}
static inline M3 Mul(const M3&a,const M3&b) return r{
 qword x=a.r[0].q,y=a.r[1].q,z=a.r[2].q;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(x),"j"(y),"j"(z),"j"(b.r[0].q));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(x),"j"(y),"j"(z),"j"(b.r[1].q));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(x),"j"(y),"j"(z),"j"(b.r[2].q));
}
// name: SafeHouse port (DrawVehiclePose)
extern "C" void DrawVehiclePose__FP3ALO(VEHICLE*p){
 V velocity,point;M3 basis;
 VTENT*method=&p->vt[33];
 velocity.q=ConvertVec(0,p,((qword (*)(VEHICLE*))method->pfn)((VEHICLE*)VT_THIS(p, method)));
 for(int i=0;i<p->cwheel;i++){
  WHEEL*e=&p->awheel[i];
  point.q=PosConvertXfs(0,(NODE*)p->space,e->node->local.position.q);
  point.f[0]=e->x;point.f[1]=e->y;
  CONTACT*hit=BestContact(p,e);
  {
   float height;
   if(hit){float limit=e->lowerZ+hit->height;if(point.f[2]<limit){point.f[2]=limit;goto heightDone;}height=limit;}
   else height=e->lowerZ;
   (void)GSmooth(point.f[2],height,g_clock.dt,D_002C21A0,0);point.f[2]=height;
  }
  heightDone:;
  point.q=PosConvertXfs(p->space,e->node->parent,point.q);
  float desired;if(i<2)desired=0.0f;else desired=p->drive/e->radius;
  if(hit){
   float current=velocity.f[0]/e->radius;
   if((0.0f<desired&&current<D_002C21CC*desired)||(desired<0.0f&&D_002C21CC*desired<current))
    e->speed=GSmooth(e->speed,D_002C21CC*desired,g_clock.dt,D_002C21B0,0);
   else e->speed=current;
  }else{
   float dt=g_clock.dt;
   void*table;
   if(Abs(e->speed)<Abs(desired))table=D_002C21B0;else table=D_002C21C0;
   e->speed=GSmooth(e->speed,desired,dt,table,0);
  }
  float dt=g_clock.dt;
  e->angle=RadNormalize(e->angle+e->speed*dt);
  basis=Mul(Rotation(g_normalZ,e->tilt),Rotation(D_002A2DB0,e->angle));
  NODE*node=e->node;
  func_00256D18(&node->matrix.position.q,point.q);
  node->matrix.basis=basis;
  node->matrix.position.f[3]=1.0f;
  node->matrix.basis.r[1].f[3]=0.0f;
  node->matrix.basis.r[0].f[3]=0.0f;
  node->matrix.basis.r[2].f[3]=0.0f;
  register int generation=++g_sw.generation;
  e->node->generation=generation;
 }
 UpdateAloXfWorlds(p);RenderSoSelf(p);
}
