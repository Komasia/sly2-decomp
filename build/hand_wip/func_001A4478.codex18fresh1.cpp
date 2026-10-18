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
static inline qword Scalar(float f){int bits;qword q;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Zero(){qword q;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(q));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword q;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(k));return q;}
static inline qword Divide(qword value,qword denominator){qword q;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(q):"j"(denominator),"j"(value));return q;}
static inline void Emit(uint value){*D_002DEA28.cur=value;D_002DEA28.cur++;}
#define CopyBlocks(S,D,W) do {const uint*source=(S);uint*destination=(D);int counter=(W)-4;do{uint a=source[0];counter-=4;uint b=source[1],c=source[2],d=source[3];destination[0]=a;source+=4;destination[1]=b;destination[2]=c;destination[3]=d;destination+=4;}while(counter>=0);}while(0)
static inline void Packet3(int index,const BLOCK3*block){Emit(0x6C03C000U|(0x15+3*index));CopyBlocks(block->words,D_002DEA28.cur,12);D_002DEA28.cur+=12;}
static inline void ClearOutput(P*p){p->matrixCount=0;p->matrixHeader=0;p->matrixPayload=0;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char uint_Size[sizeof(uint)==4?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
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
extern "C" void func_001A4478(WORLD*world,M4*transform,P*incoming){
 register P*p __asm__("$17");__asm__("daddu %0,%1,$zero":"=r"(p):"r"(incoming));
 WORK w;qword input=p->input->q;w.point.q=input;
 if(transform){register qword r3 __asm__("vf4"),r0 __asm__("vf3"),r1 __asm__("vf2"),r2 __asm__("vf1"),point __asm__("vf5");
  __asm__("lqc2 %0,%5\n\tlqc2 %1,%6\n\tlqc2 %2,%7\n\tlqc2 %3,%8\n\tqmtc2.ni %9,%4":"=j"(r3),"=j"(r0),"=j"(r1),"=j"(r2),"=j"(point):"m"(transform->row[3].q),"m"(transform->row[0].q),"m"(transform->row[1].q),"m"(transform->row[2].q),"r"(input));
  __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddaz.xyz $ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(point):"j"(r0),"j"(r1),"j"(r2),"j"(r3));w.point.q=point;
 }
 register qword queryPoint __asm__("$5");__asm__("lq %0,%1":"=r"(queryPoint):"m"(w.point.q));
 func_001A3F78(world,queryPoint,4,w.results);
 if(p->packetStrength==0.0f){p->packetCount=0;p->packetBegin=0;}
 else{
  p->packetBegin=(U*)D_002DEA28.cur;int index=0;
  unsigned slot=0;OBJECT*object=w.results[0].object;
  for(;slot<4&&object;){Packet3(index,&object->packet);index++;slot++;if(slot<4)object=w.results[slot].object;}
  while(index<4){Packet3(index,&D_002BFC60);index++;}
  uint*cursor=D_002DEA28.cur;while((uint)cursor&15){*cursor=0;cursor=++D_002DEA28.cur;}
  p->packetCount=(U*)D_002DEA28.cur-p->packetBegin;
 }
 if(p->distanceLimit==0.0f){ClearOutput(p);return;}
 float total=0.0f;qword sum=Zero();
 RESULT*result=w.results;unsigned i=0;OBJECT*object=result->object;
 for(;;){
  if(i>=4||!object)break;
  if(object->enabled){
   int kind=object->kind;register float magnitude __asm__("$f0")=D_002BFC90;
   switch(kind){
   case 1:{
    register float weight __asm__("$f0");register VE*table __asm__("$3");U cached;
    register uint word __asm__("$2");register qword factor __asm__("vf2");
    __asm__("lwc1 %0,%3\n\tlw %1,%4\n\tmfc1 %2,%0":"=f"(weight),"=r"(table),"=r"(word):"m"(result->weight),"m"(object->vt));__asm__("qmtc2.ni %1,%0":"=j"(factor):"r"(word));
    register int delta __asm__("$4");register M4*(*method)(void*) __asm__("$2");
    __asm__("lh %0,%3\n\tlw %1,%4\n\tadd.s %2,%2,%5":"=r"(delta),"=r"(method),"+f"(total):"m"(table[31].delta),"m"(table[31].fn),"f"(weight));
    register void*receiver __asm__("$4");
    __asm__("sqc2 %5,%1\n\taddu %0,%3,%4\n\tsqc2 %5,%2":"=r"(receiver),"=m"(w.scalar.q),"=m"(cached.q):"r"(object),"r"(delta),"j"(factor));
    M4*m=method(receiver);
    {register qword position __asm__("vf1")=m->row[3].q,factor __asm__("vf2")=cached.q;
     __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(sum):"j"(position),"j"(factor));}
    break;
   }
   case 0:{
    register float offsetValue __asm__("$f0")=magnitude,weight __asm__("$f1");
    register qword weightVector __asm__("vf3"),offsetPosition __asm__("vf2"),point __asm__("vf5"),direction __asm__("vf1");register uint word __asm__("$2");
    __asm__("lwc1 %0,%3\n\tneg.s %1,%1\n\tlqc2 %2,%4":"=f"(weight),"+f"(offsetValue),"=j"(point):"m"(result->weight),"m"(w.point.q));
    __asm__("mfc1 %0,%1":"=r"(word):"f"(weight));
    __asm__("qmtc2.ni %2,%0\n\tadd.s %1,%1,%3":"=j"(weightVector),"+f"(total):"r"(word),"f"(weight));
    __asm__("mfc1 %0,%1":"=r"(word):"f"(offsetValue));__asm__("qmtc2.ni %1,%0":"=j"(offsetPosition):"r"(word));
    __asm__("sqc2 %1,%0":"=m"(w.scalar.q):"j"(offsetPosition));
    __asm__("lqc2 %0,%2\n\tsqc2 %3,%1":"=j"(direction),"=m"(w.scalar.q):"m"(object->direction.q),"j"(weightVector));
    __asm__("vadda.xyzw $ACC,%2,$vf0\n\tvmaddx.xyzw %1,%3,%1x\n\tvadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%4x":"+j"(sum),"+&j"(offsetPosition):"j"(point),"j"(direction),"j"(weightVector));break;
   }
   }
  }
  i++;result++;if(i>=4)break;object=result->object;
 }
 if(total==0.0f){ClearOutput(p);return;}
 qword direction;float distance,threshold;
 {register uint totalWord __asm__("$2");register qword divisor __asm__("vf2"),point __asm__("vf3"),mean __asm__("vf1"),delta __asm__("vf4");
  __asm__("mfc1 %0,%1":"=r"(totalWord):"f"(total));__asm__("qmtc2.ni %2,%0\n\tlqc2 %1,%3":"=j"(divisor),"=j"(point):"r"(totalWord),"m"(w.point.q));
  register uint thresholdPage __asm__("$2");register float thresholdFactor __asm__("$f1");
  __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%3,$Q\n\tlui %1,%%hi(%4)":"=j"(mean),"=r"(thresholdPage):"j"(divisor),"j"(sum),"i"(&D_002BFC94));
  __asm__("sqc2 %3,%0\n\tvsub.xyzw %1,%4,%3\n\tlwc1 %2,%%lo(%6)(%5)":"=m"(w.center.q),"=j"(delta),"=f"(thresholdFactor):"j"(mean),"j"(point),"r"(thresholdPage),"i"(&D_002BFC94),"m"(*(float*)(thresholdPage-0x36C)));direction=delta;
  register qword norm __asm__("vf1"),one __asm__("vf3");register float limit __asm__("$f0"),measured __asm__("$f21");register uint word __asm__("$2");
  __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tlwc1 %2,%4":"=&j"(norm),"=&j"(one),"=f"(limit):"j"(delta),"m"(p->distanceLimit));
  __asm__("qmfc2.ni %1,%3\n\tmtc1 %1,%0\n\tmul.s %2,%2,%4":"=&f"(measured),"=&r"(word),"+f"(thresholdFactor):"j"(norm),"f"(limit));
  distance=measured;threshold=thresholdFactor;w.scalar.q=divisor;
 }
 if(distance<threshold){
  if(distance<1.0f)direction=D_002A2DC0.q;
  else{qword d=Scalar(distance);w.scalar.q=d;direction=Divide(direction,d);}
  register float negative __asm__("$f0");register qword point __asm__("vf2");__asm__("neg.s %0,%2\n\tlqc2 %1,%3":"=f"(negative),"=j"(point):"f"(threshold),"m"(w.point.q));distance=threshold;qword k=Scalar(negative);w.center.q=AddScaled(point,direction,k);w.scalar.q=k;
 }else{qword d=Scalar(distance);w.scalar.q=d;direction=Divide(direction,d);}
 register float extent __asm__("$f20");register uint axisBAddress __asm__("$3"),axisAAddress __asm__("$2");
 __asm__("lwc1 %0,%3\n\tlui %1,%%hi(%4)\n\tlui %2,%%hi(%5)":"=f"(extent),"=r"(axisBAddress),"=r"(axisAAddress):"m"(p->extraDistance),"i"(&D_002A2DB0),"i"(&D_002A2DA0));
 __asm__("addiu %0,%0,%%lo(%2)\n\taddiu %1,%1,%%lo(%3)":"+r"(axisBAddress),"+r"(axisAAddress):"i"(&D_002A2DB0),"i"(&D_002A2DA0));
 register qword axisB __asm__("$5"),axisA __asm__("$6");
 __asm__("lq %0,%3\n\tlq %1,%4\n\tadd.s %2,%5,%2":"=&r"(axisB),"=r"(axisA),"+f"(extent):"m"(*(U*)axisBAddress),"m"(*(U*)axisAAddress),"f"(distance));
 func_0011E2D8(direction,axisB,axisA,&w.basis);
 uint*packetWords=w.packet.words;PACKET5*packet=(PACKET5*)packetWords;
 {register uint bits __asm__("$2");register qword factor __asm__("vf2"),savedDirection __asm__("vf4"),row __asm__("vf1");
  __asm__("mfc1 %0,%1":"=r"(bits):"f"(extent));
  __asm__("qmtc2.ni %1,%0":"=j"(factor):"r"(bits));savedDirection=direction;
  __asm__("vmulx.xyzw %0,%1,%2x":"=j"(row):"j"(savedDirection),"j"(factor));
  __asm__("sqc2 %1,%0":"=m"(w.basis.row[2].q):"j"(row));w.scalar.q=factor;
  (void)func_00256D18(&packet->data.position,w.center.q);
 }
 register qword row0 __asm__("$3"),row1 __asm__("$2");
 register float fraction __asm__("$f3");
 __asm__("lq %0,%2\n\tdiv.s %1,%3,%4":"=r"(row0),"=f"(fraction):"m"(w.basis.row[0].q),"f"(distance),"f"(extent));
 register uint cameraPage __asm__("$7");
 __asm__("lq %0,%2\n\tlui %1,%%hi(%3)":"=r"(row1),"=r"(cameraPage):"m"(w.basis.row[1].q),"i"(&D_002DDF40));
 register CAMERA*camera __asm__("$7");__asm__("sq %2,%1\n\taddiu %0,%3,%%lo(%4)":"=r"(camera),"=m"(packet->data.basis.row[0].q):"r"(row0),"r"(cameraPage),"i"(&D_002DDF40));
 register float one __asm__("$f1")=1.0f;
 register float radius __asm__("$f2")=p->distanceLimit;
 packet->data.basis.row[1].q=row1;
 register float farRadius __asm__("$f20"),farScalar __asm__("$f0");
 __asm__("mul.s %0,%2,%3\n\tli.s %1,%F4":"=f"(farRadius),"=f"(farScalar):"f"(radius),"f"(extent),"F"(1.5f));
 {register qword row __asm__("$2");__asm__("lq %0,%3\n\tsq %0,%1\n\tdiv.s %2,%2,%4":"=&r"(row),"=m"(packet->data.basis.row[2].q),"+f"(farRadius):"m"(w.basis.row[2].q),"f"(distance));}
 w.packet.data.basis.row[2].i[3]=0;w.packet.data.basis.row[1].i[3]=0;w.packet.data.basis.row[0].i[3]=0;
 {register uint bits __asm__("$2");register qword factor __asm__("vf3"),row __asm__("vf1"),center __asm__("vf4"),far __asm__("vf2"),middle __asm__("vf1");
  __asm__("swc1 %2,%1\n\tmfc1 %0,%3":"=r"(bits),"=m"(packet->data.position.f[3]):"f"(one),"f"(farScalar));
  __asm__("qmtc2.ni %3,%0\n\tlqc2 %1,%4\n\tlqc2 %2,%5":"=j"(factor),"=j"(row),"=j"(center):"r"(bits),"m"(w.basis.row[2].q),"m"(w.center.q));
  __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(far):"j"(center),"j"(row),"j"(factor));
  register qword point __asm__("$2"),cameraPoint __asm__("$4");register float cameraRadius __asm__("$f12");
  __asm__("lq %0,%4\n\tlq %1,%5\n\tvadd.xyzw %2,%6,%7\n\tlwc1 %3,%8":"=r"(point),"=r"(cameraPoint),"=j"(middle),"=f"(cameraRadius):"m"(w.point.q),"m"(camera->position.q),"j"(center),"j"(row),"m"(camera->radius));
  w.packet.data.fraction=fraction;
  w.spheres[0].position.q=point;w.spheres[1].position.q=middle;w.spheres[1].radius.value=farRadius;
  w.spheres[2].position.q=far;w.spheres[0].radius.value=radius;w.scalar.q=factor;w.spheres[2].radius.bits=0;
  int kind=func_001A4258(cameraPoint,cameraRadius,3,w.spheres);
  register uint vifsAddress __asm__("$3");__asm__("lui %0,%%hi(%1)":"=r"(vifsAddress):"i"(&D_002DEA28));
  w.packet.data.kind=kind;
  register VIFS*writer __asm__("$5");register uint vifsPage __asm__("$15");
  __asm__("addiu %0,%2,%%lo(%3)\n\tdaddu %1,%2,$zero":"=&r"(writer),"=r"(vifsPage):"r"(vifsAddress),"i"(&D_002DEA28));
  uint*header=writer->cur;U*payload=(U*)(header+4);p->matrixHeader=(U*)header;p->matrixPayload=payload;
  register uint*cursor __asm__("$4");__asm__("lw %0,%1":"=r"(cursor):"m"(writer->cur));
  while(((uint)cursor&15)!=12){*cursor=0;cursor=++writer->cur;}
  register VIFS*copyWriter __asm__("$8");__asm__("addiu %0,%1,%%lo(%2)":"=r"(copyWriter):"r"(vifsPage),"i"(&D_002DEA28));
  *copyWriter->cur=0x6C05C00EU;
  uint*next=copyWriter->cur+1;register uint*destination __asm__("$6");
  __asm__("daddu %0,%2,$zero\n\tsw %2,%1":"=&r"(destination),"=m"(copyWriter->cur):"r"(next));
  int counter=16;
  do{const uint*source=packetWords;uint a=source[0];counter-=4;uint b=source[1];register uint c __asm__("$4"),d __asm__("$5");
   __asm__("lw %0,%2\n\tlw %1,%3":"=&r"(c),"=r"(d):"m"(source[2]),"m"(source[3]));
   destination[0]=a;packetWords+=4;destination[1]=b;destination[2]=c;destination[3]=d;destination+=4;}while(counter>=0);
  register VIFS*reader __asm__("$4");__asm__("addiu %0,%1,%%lo(%2)":"=r"(reader):"r"(vifsPage),"i"(&D_002DEA28));
  copyWriter->cur+=20;
  register uint*end __asm__("$2");__asm__("lw %0,%1":"=r"(end):"m"(reader->cur));p->matrixCount=(U*)end-p->matrixHeader;
 }
}
