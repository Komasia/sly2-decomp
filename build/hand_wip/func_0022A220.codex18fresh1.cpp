// Clip the camera-to-source curtain against nearby collision faces.
typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct O;
struct EDGE {unsigned short first,second,pad4,face;EDGE *next;};
struct FACE {V equation;EDGE *edge;int field14,flags,field1c;};
struct NODE {NODE *first,*second;FACE *face;};
struct TREE {int field0,field4,count;NODE *nodes;};
struct O {char pad0[0x68];TREE tree;char pad78[0x1c];V *vertices;int field98;FACE *faces;char pada0[0xc8];O *source;char pad16c[0xc];int frame,hit;float height;};
struct CAMERA {char pad0[0x90];V position;char pada0[0x404];int frame;};
struct WORLD;
struct FRAME {};
struct REQUEST {unsigned size,alignment;};
union TEMP {V scalar;REQUEST request;};
struct OUTPUT {int objectCount;O **objects;int capacity;FACE **end;};
struct PAIR {V value,one;};
struct WORK {V corner[4],side[4];TEMP temp;FRAME frame;V normal;OUTPUT output;PAIR distance[6];V camera,source,plane,first,second;O ***objectsOutput;V reused,firstBoundary,crossing;};
extern CAMERA D_002DDF40;
extern float D_002C4490;
extern V D_002A2DC0;
extern WORLD D_003DD490;
extern "C" {
qword func_001A62E8(O *);
void func_00119308(V *,qword,qword,qword);
void func_00119390(V *,qword,qword);
V *func_002564C0(V *);
V *func_002564B8(V *);
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *,int);
void *func_001AE318(REQUEST *);
int func_0014F030(void *,O *);
void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,O *),void *,int *,O ***);
int func_00118D08(NODE *,NODE *,int,V *,int *,FACE ***);
}
static inline qword ToVF(qword input){qword value;asm("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}
static inline qword ToCPU(qword input){qword value;asm("qmfc2.ni %0,%1":"=r"(value):"j"(input));return value;}
static inline qword Scalar(float input){qword value;asm("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}
static inline void Snapshot(V &home,qword input){asm("sqc2 %1,%0":"=m"(home.q):"j"(input));}
static inline void SnapshotCPU(V &home,qword input){asm("sq %1,%0":"=m"(home.q):"r"(input));}
static inline float ScalarX(qword input){float value;asm("qmfc2.ni %0,%1":"=r"(value):"j"(input));return value;}
static inline qword Sub(qword first,qword second){qword value;asm("vsub.xyzw %0,%1,%2":"=j"(value):"j"(first),"j"(second));return value;}
static inline qword CurtainInputs(qword source,const V &camera,qword &cameraResult,qword &heightResult,qword &upResult){
 register qword sourceVF asm("vf5"),cameraVF asm("vf4"),heightVF asm("vf2"),upVF asm("vf1");
 asm("lui $3,%%hi(%6)\n\tlui $2,%%hi(%7)\n\taddiu $2,$2,%%lo(%7)\n\tlw $3,%%lo(%6)($3)\n\tqmtc2.ni %4,%0\n\tlqc2 %1,%5\n\tqmtc2.ni $3,%2\n\tlqc2 %3,0($2)"
 :"=j"(sourceVF),"=j"(cameraVF),"=j"(heightVF),"=j"(upVF):"r"(source),"m"(camera.q),"i"(&D_002C4490),"i"(&D_002A2DC0):"$2","$3","memory");
 cameraResult=cameraVF;heightResult=heightVF;upResult=upVF;return sourceVF;
}
static inline qword Top(qword position,qword up,qword scalar){qword value;asm("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(value):"j"(position),"j"(up),"j"(scalar));return value;}
static inline qword Max(qword first,qword second){qword value;asm("vmax.xyz %0,%1,%2":"=j"(value):"j"(first),"j"(second));return value;}
static inline qword Min(qword first,qword second){qword value;asm("vmini.xyz %0,%1,%2":"=j"(value):"j"(first),"j"(second));return value;}
static inline qword SideNormal(qword edge,qword plane,V &copy){
 qword cross=edge,length,one,result;
 asm("vopmula.xyz ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(cross):"j"(plane));
 SnapshotCPU(copy,ToCPU(plane));
 asm("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(length),"=&j"(one):"j"(cross));
 asm("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(length));
 asm("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(result):"j"(cross),"j"(length));return result;
}
static inline float LengthXY(qword vector){qword square,length;
 asm("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(square):"j"(vector));
 asm("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(square));return ScalarX(length);
}
static inline float Z(qword vector){float value;asm("pextuw %0,$zero,%1":"=r"(value):"r"(vector));return value;}
static inline float Slope(qword vector){float z=Z(ToCPU(vector));return z/LengthXY(vector);}
static inline float DistanceFirst(PAIR &home,const V &plane,const V &point){
 func_002564B8(&home.value);func_002564B8(&home.one);
 register qword p asm("vf3")=plane.q,x asm("vf4")=point.q;
 register qword value asm("vf1"),one asm("vf2");
 asm("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"=j"(value),"=&j"(one):"j"(p),"j"(x));
 float result=ScalarX(value);Snapshot(home.one,one);Snapshot(home.value,value);return result;
}
static inline float DistanceSecond(PAIR &home,const V &plane,const V &point){
 func_002564B8(&home.value);func_002564B8(&home.one);
 register qword p asm("vf3")=plane.q,x asm("vf4")=point.q;
 register qword value asm("vf2"),one asm("vf1");
 asm("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"=j"(value),"=&j"(one):"j"(p),"j"(x));
 float result=ScalarX(value);Snapshot(home.one,one);Snapshot(home.value,value);return result;
}
static inline float BoundaryFirst(PAIR &home,const V &plane,const V &point){
 func_002564B8(&home.value);func_002564B8(&home.one);
 register qword value asm("vf3")=plane.q,x asm("vf4")=point.q,one asm("vf1");
 asm("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w":"+j"(value),"=&j"(one):"j"(x));
 float result=ScalarX(value);Snapshot(home.one,one);Snapshot(home.value,value);return result;
}
static inline float BoundaryOther(PAIR &home,const V &plane,const V &point){
 func_002564B8(&home.value);func_002564B8(&home.one);
 register qword value asm("vf1")=plane.q,x asm("vf4")=point.q,one asm("vf2");
 asm("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w":"+j"(value),"=&j"(one):"j"(x));
 float result=ScalarX(value);Snapshot(home.one,one);Snapshot(home.value,value);return result;
}
static inline qword Crossing(qword first,qword second,float fraction,V &home){
 qword u=Scalar(fraction),v=Scalar(1.0f-fraction),point;
 asm("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(point):"j"(first),"j"(second),"j"(v),"j"(u));
 Snapshot(home,v);Snapshot(home,u);return point;
}
static inline V *SideStorage(WORK &work){V *value;asm("addiu %0,%1,%2":"=r"(value):"r"(&work),"i"((unsigned)&((WORK *)0)->side));return value;}
static inline void CopyVF(V &out,const V &in){qword value;asm("lqc2 %0,%1":"=j"(value):"m"(in.q));Snapshot(out,value);}
extern "C" void func_0022A220(O *owner){
 WORK work;
 if(owner->frame==D_002DDF40.frame)return;
 owner->frame=D_002DDF40.frame;
 work.camera.q=D_002DDF40.position.q;
 O *source=owner->source;if(!source)source=owner;
 qword position=func_001A62E8(source);
 owner->hit=0;owner->height=0.0f;
 work.source.q=position;
 qword height,up,camera;
 qword sourcePosition=CurtainInputs(position,work.camera,camera,height,up);
 work.corner[2].q=Top(camera,up,height);
 work.corner[1].q=Top(sourcePosition,up,height);
 work.corner[0].q=ToCPU(sourcePosition);work.corner[3].q=ToCPU(camera);
 Snapshot(work.temp.scalar,height);
 func_00119308(&work.temp.scalar,work.camera.q,position,work.corner[1].q);
 work.plane.q=work.temp.scalar.q;
 work.objectsOutput=&work.output.objects;
 V *sideStorage=SideStorage(work);
 for(int i=0;i<4;++i){
  work.reused.q=Sub(work.corner[(i+1)%4].q,work.corner[i].q);
  func_002564C0(&work.normal);
  qword normal=SideNormal(work.reused.q,work.plane.q,work.normal);
  func_00119390(&sideStorage[i],ToCPU(normal),work.corner[i].q);
 }
 func_001AE478(&work.frame);
 work.temp.request.size=0x10000;work.temp.request.alignment=16;
 FACE **faces=(FACE **)func_001AE318(&work.temp.request);
 qword broadHeight=Scalar(D_002C4490);
 qword lower=Min(work.camera.q,work.source.q),upper=Top(Max(work.camera.q,work.source.q),D_002A2DC0.q,broadHeight);
 Snapshot(work.temp.scalar,broadHeight);
 func_0020FAA0(&D_003DD490,ToCPU(lower),ToCPU(upper),func_0014F030,0,&work.output.objectCount,work.objectsOutput);
 float maximum=Slope(Sub(work.source.q,work.camera.q)),original=maximum;
 for(int objectIndex=0;objectIndex<work.output.objectCount;++objectIndex){
  O *object=work.output.objects[objectIndex];TREE *tree=&object->tree;
  work.output.capacity=0x4000;work.output.end=faces;
  switch(func_00118D08(tree->nodes,tree->nodes+tree->count,4,work.corner,&work.output.capacity,&work.output.end)){
   case 0:func_001AE4A0(&work.frame,2);return;
   case 1:continue;
   case 2:break;
   default:break;
  }
  int count=work.output.end-faces;
  for(int faceIndex=0;faceIndex<count;++faceIndex){
   for(EDGE *edge=faces[faceIndex]->edge;edge;edge=edge->next){
    if(object->faces[edge->face].flags&0x4000){
     float zero=0.0f;
     qword firstPoint=object->vertices[edge->first].q,secondPoint=object->vertices[edge->second].q;
     work.first.q=firstPoint;work.second.q=secondPoint;
     float first=DistanceFirst(work.distance[0],work.plane,work.first);
     float second=DistanceSecond(work.distance[1],work.plane,work.second);
     if(zero<first&&zero<second)continue;
     if(first<zero&&second<zero)continue;
     float fraction=first/(first-second);
     CopyVF(work.firstBoundary,work.side[0]);
     work.crossing.q=Crossing(work.first.q,work.second.q,fraction,work.temp.scalar);
     int inside=0;
     if(BoundaryFirst(work.distance[2],work.firstBoundary,work.crossing)<zero){
      CopyVF(work.reused,work.side[1]);
      if(BoundaryOther(work.distance[3],work.reused,work.crossing)<zero){
       CopyVF(work.reused,work.side[2]);
       if(BoundaryOther(work.distance[4],work.reused,work.crossing)<zero){
        CopyVF(work.reused,work.side[3]);
        if(BoundaryOther(work.distance[5],work.reused,work.crossing)<zero)inside=1;
       }
      }
     }
     if(inside){float slope=Slope(Sub(work.crossing.q,work.camera.q));if(maximum<slope)maximum=slope;}
    }
   }
  }
  for(FACE **cursor=faces;count>0;--count,++cursor)(*cursor)->flags&=~0x4000;
 }
 owner->hit=1;owner->height=(maximum-original)*LengthXY(Sub(work.camera.q,work.source.q));
 func_001AE4A0(&work.frame,2);
}
