typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};union F{float value;int bits;};
struct M3{U row[3];};struct M4{U row[4];};
union BLOCK3{float f[12];uint words[12];};
struct VE{short delta,pad;void*fn;};
struct OBJECT{char pad0[12];VE*vt;char pad10[0xA0-0x10];U direction;char padB0[0x30];int kind;char padE4[0x120-0xE4];BLOCK3 packet;char pad150[8];int enabled;};
struct RESULT{float weight;OBJECT*object;};
struct P{char pad0[4];U*input;char pad8[8];float packetStrength;int packetCount;U*packetBegin;float distanceLimit,extraDistance;U*matrixPayload;int matrixCount;U*matrixHeader;};
struct VIFS{char pad0[12];uint*cur;};
struct CAMERA{char pad0[0x48];float radius;char pad4C[0x90-0x4C];U position;};
struct SPHERE{U position;F radius;};
union PACKET5{struct{M3 basis;U position;int kind;float fraction;}data;uint words[20];};
struct WORK{RESULT results[4];U scalar;M3 basis;PACKET5 packet;SPHERE spheres[3];U point,center;};
struct WORLD;
extern "C"{
 void func_001A3F78(WORLD*,qword,int,RESULT*);
 void func_0011E2D8(qword,qword,qword,M3*);
 void*func_00256D18(U*,qword);
 int func_001A4258(qword,float,int,SPHERE*);
 extern VIFS D_002DEA28;extern CAMERA D_002DDF40;
 extern BLOCK3 D_002BFC60;extern float D_002BFC90,D_002BFC94;
 extern U D_002A2DC0,D_002A2DB0,D_002A2DA0;
}
static inline M4*GetMatrix(OBJECT*p){VE&v=p->vt[31];return ((M4*(*)(void*))v.fn)((char*)p+v.delta);}
static inline qword Transform(const M4*m,qword p){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(p));__asm__("vmulax.xyz $ACC,%1,%3x\n\tvmadday.xyz $ACC,%2,%3y\n\tvmaddaz.xyz $ACC,%4,%3z\n\tvmaddw.xyz %0,%5,$vf0w":"+j"(v):"j"(m->row[0].q),"j"(m->row[1].q),"j"(v),"j"(m->row[2].q),"j"(m->row[3].q));return v;}
static inline qword Scalar(float f){int bits;qword q;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Zero(){qword q;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(q));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword q;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(k));return q;}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Difference(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Scale(qword a,qword b){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Divide(qword value,qword denominator){qword q;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(q):"j"(denominator),"j"(value));return q;}
static inline float Length(qword value){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(value));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline void Emit(uint value){*D_002DEA28.cur=value;D_002DEA28.cur++;}
static inline void CopyBlocks(const uint*source,uint*destination,int words){
 int counter=words-4;
 do{uint a=source[0];counter-=4;uint b=source[1],c=source[2],d=source[3];destination[0]=a;source+=4;destination[1]=b;destination[2]=c;destination[3]=d;destination+=4;}while(counter>=0);
}
static inline void Packet3(int index,const BLOCK3*block){Emit(0x6C03C000U|(0x15+3*index));CopyBlocks(block->words,D_002DEA28.cur,12);D_002DEA28.cur+=12;}
static inline void ClearOutput(P*p){p->matrixCount=0;p->matrixHeader=0;p->matrixPayload=0;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char F_Size[sizeof(F)==4?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char M4_Size[sizeof(M4)==64?1:-1];
typedef char BLOCK3_Size[sizeof(BLOCK3)==48?1:-1];
typedef char OBJECT_Size[sizeof(OBJECT)==352?1:-1];
typedef char RESULT_Size[sizeof(RESULT)==8?1:-1];
typedef char P_Size[sizeof(P)==48?1:-1];
typedef char VIFS_Size[sizeof(VIFS)==16?1:-1];
typedef char CAMERA_Size[sizeof(CAMERA)==160?1:-1];
typedef char SPHERE_Size[sizeof(SPHERE)==32?1:-1];
typedef char PACKET5_Size[sizeof(PACKET5)==80?1:-1];
typedef char WORK_Size[sizeof(WORK)==304?1:-1];
typedef char OBJECT_vt_Offset[FIELD_OFFSET(OBJECT,vt)==12?1:-1];
typedef char OBJECT_direction_Offset[FIELD_OFFSET(OBJECT,direction)==160?1:-1];
typedef char OBJECT_kind_Offset[FIELD_OFFSET(OBJECT,kind)==224?1:-1];
typedef char OBJECT_packet_Offset[FIELD_OFFSET(OBJECT,packet)==288?1:-1];
typedef char OBJECT_enabled_Offset[FIELD_OFFSET(OBJECT,enabled)==344?1:-1];
typedef char RESULT_weight_Offset[FIELD_OFFSET(RESULT,weight)==0?1:-1];
typedef char RESULT_object_Offset[FIELD_OFFSET(RESULT,object)==4?1:-1];
typedef char P_input_Offset[FIELD_OFFSET(P,input)==4?1:-1];
typedef char P_packetStrength_Offset[FIELD_OFFSET(P,packetStrength)==16?1:-1];
typedef char P_packetCount_Offset[FIELD_OFFSET(P,packetCount)==20?1:-1];
typedef char P_packetBegin_Offset[FIELD_OFFSET(P,packetBegin)==24?1:-1];
typedef char P_distanceLimit_Offset[FIELD_OFFSET(P,distanceLimit)==28?1:-1];
typedef char P_extraDistance_Offset[FIELD_OFFSET(P,extraDistance)==32?1:-1];
typedef char P_matrixPayload_Offset[FIELD_OFFSET(P,matrixPayload)==36?1:-1];
typedef char P_matrixCount_Offset[FIELD_OFFSET(P,matrixCount)==40?1:-1];
typedef char P_matrixHeader_Offset[FIELD_OFFSET(P,matrixHeader)==44?1:-1];
typedef char VIFS_cur_Offset[FIELD_OFFSET(VIFS,cur)==12?1:-1];
typedef char CAMERA_radius_Offset[FIELD_OFFSET(CAMERA,radius)==72?1:-1];
typedef char CAMERA_position_Offset[FIELD_OFFSET(CAMERA,position)==144?1:-1];
typedef char SPHERE_position_Offset[FIELD_OFFSET(SPHERE,position)==0?1:-1];
typedef char SPHERE_radius_Offset[FIELD_OFFSET(SPHERE,radius)==16?1:-1];
typedef char WORK_results_Offset[FIELD_OFFSET(WORK,results)==0?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==32?1:-1];
typedef char WORK_basis_Offset[FIELD_OFFSET(WORK,basis)==48?1:-1];
typedef char WORK_packet_Offset[FIELD_OFFSET(WORK,packet)==96?1:-1];
typedef char WORK_spheres_Offset[FIELD_OFFSET(WORK,spheres)==176?1:-1];
typedef char WORK_point_Offset[FIELD_OFFSET(WORK,point)==272?1:-1];
typedef char WORK_center_Offset[FIELD_OFFSET(WORK,center)==288?1:-1];
typedef char Packet_Basis[FIELD_OFFSET(PACKET5,data.basis)==0?1:-1];
typedef char Packet_Position[FIELD_OFFSET(PACKET5,data.position)==48?1:-1];
typedef char Packet_Kind[FIELD_OFFSET(PACKET5,data.kind)==64?1:-1];
typedef char Packet_Fraction[FIELD_OFFSET(PACKET5,data.fraction)==68?1:-1];
extern "C" void func_001A4478(WORLD*world,M4*transform,P*p){
 WORK w;w.point.q=p->input->q;
 if(transform)w.point.q=Transform(transform,w.point.q);
 func_001A3F78(world,w.point.q,4,w.results);
 if(p->packetStrength==0.0f){p->packetCount=0;p->packetBegin=0;}
 else{
  p->packetBegin=(U*)D_002DEA28.cur;int index=0;
  unsigned slot=0;OBJECT*object=w.results[0].object;
  for(;slot<4&&object;){Packet3(index,&object->packet);index++;slot++;if(slot<4)object=w.results[slot].object;}
  while(index<4){Packet3(index,&D_002BFC60);index++;}
  while((uint)D_002DEA28.cur&15)Emit(0);
  p->packetCount=(U*)D_002DEA28.cur-p->packetBegin;
 }
 if(p->distanceLimit==0.0f){ClearOutput(p);return;}
 float total=0.0f;qword sum=Zero();
 RESULT*result=w.results;unsigned i=0;OBJECT*object=result->object;
 for(;;){
  if(i>=4||!object)break;
  if(object->enabled){
   switch(object->kind){
   case 1:{
    float weight=result->weight;qword k=Scalar(weight);total+=weight;w.scalar.q=k;
    M4*m=GetMatrix(object);qword cached=w.scalar.q;sum=AddScaled(sum,m->row[3].q,cached);break;
   }
   case 0:{
    float offsetValue=-D_002BFC90;float weight=result->weight;qword k=Scalar(weight);total+=weight;
    qword offset=Scalar(offsetValue);w.scalar.q=offset;qword position=AddScaled(w.point.q,object->direction.q,offset);w.scalar.q=k;sum=AddScaled(sum,position,k);break;
   }
   }
  }
  i++;result++;if(i>=4)break;object=result->object;
 }
 if(total==0.0f){ClearOutput(p);return;}
 qword divisor=Scalar(total);w.center.q=Divide(sum,divisor);
 qword direction=Difference(w.point.q,w.center.q);float distance=Length(direction),threshold=D_002BFC94*p->distanceLimit;w.scalar.q=divisor;
 if(distance<threshold){
  if(distance<1.0f)direction=D_002A2DC0.q;
  else{qword d=Scalar(distance);w.scalar.q=d;direction=Divide(direction,d);}
  qword k=Scalar(-threshold);w.center.q=AddScaled(w.point.q,direction,k);w.scalar.q=k;distance=threshold;
 }else{qword d=Scalar(distance);w.scalar.q=d;direction=Divide(direction,d);}
 float extent=distance+p->extraDistance;
 func_0011E2D8(direction,D_002A2DB0.q,D_002A2DA0.q,&w.basis);
 qword k=Scalar(extent);w.basis.row[2].q=Scale(direction,k);
 w.scalar.q=k;(void)func_00256D18(&w.packet.data.position,w.center.q);
 w.packet.data.basis=w.basis;
 w.packet.data.basis.row[2].i[3]=w.packet.data.basis.row[1].i[3]=w.packet.data.basis.row[0].i[3]=0;
 w.packet.data.position.f[3]=1.0f;
 w.packet.data.fraction=distance/extent;
 float radius=p->distanceLimit;
 w.spheres[0].position=w.point;w.spheres[0].radius.value=radius;
 w.spheres[1].position.q=Add(w.center.q,w.basis.row[2].q);w.spheres[1].radius.value=radius*extent/distance;
 qword far=Scalar(1.5f);w.spheres[2].position.q=AddScaled(w.center.q,w.basis.row[2].q,far);w.spheres[2].radius.bits=0;w.scalar.q=far;
 w.packet.data.kind=func_001A4258(D_002DDF40.position.q,D_002DDF40.radius,3,w.spheres);
 p->matrixHeader=(U*)D_002DEA28.cur;p->matrixPayload=(U*)(D_002DEA28.cur+4);
 while(((uint)D_002DEA28.cur&15)!=12)Emit(0);
 Emit(0x6C05C00EU);CopyBlocks(w.packet.words,D_002DEA28.cur,20);D_002DEA28.cur+=20;
 p->matrixCount=(U*)D_002DEA28.cur-p->matrixHeader;
}
