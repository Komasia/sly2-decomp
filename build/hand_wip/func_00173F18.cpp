
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M3{U row[3];M3(){}M3(const M3&m){row[0]=m.row[0];row[1]=m.row[1];row[2]=m.row[2];}M3&operator=(const M3&m){row[0]=m.row[0];row[1]=m.row[1];row[2]=m.row[2];return*this;}};
inline void*operator new(unsigned,void*p){return p;}
struct M4{U row[4];};
struct LM{float low,high;};
struct P{char pad0[0x28];unsigned long flags;char pad30[8];float radius;char pad3C[0x144];void*blocked;};
struct ENTRY{int kind,unknown4;P*object;char padC[8];int busy;float until;};
struct SET{char pad0[0x50];int count;ENTRY*entries;char pad58[0x38];int radiusCount;P**radiusObjects;int pointCount;qword*points;};
struct CAMERA{char pad0[0x60];qword direction;};
struct HEAP{};
struct QUERY{int count;void**objects;qword*outPoint;M3*outBasis;int*outFlip;ENTRY*selected;int flip;};
struct SAMPLE{U position,direction,scalar;};
struct ROWS{U row[3];};
union SCRATCH{ROWS basis;SAMPLE sample;};
struct WORK{HEAP heap;U bestPoint;M3 bestBasis;SCRATCH scratch;M3 rotation;QUERY query;U candidate,input;int next;};
extern "C"{
extern float D_002A53E0,D_002DDED0,D_002BE5E4,D_002BE5E8;extern LM D_002BBB60;extern CAMERA D_002DDF40;extern qword D_002A2DC0;
void*func_001AE478(void*);void func_001AE4A0(void*,int);void func_001B44D8(int*,void***);
qword func_001A62E8(P*);M4*func_001A6318(P*);
int func_00173768(SET*,qword,int,void**,float);
float func_001E6648(P*);LM*func_001EA3B0(void*,float);void func_001E6F10(P*,qword*,qword*,float);
float func_0011D448(float,float);float func_002458F0(float,float);M3 func_0011B500(qword,float);
}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline int Nearest(float f){float n;int result;__asm__("cvt.w.s %0,%1":"=f"(n):"f"(f));__asm__("mfc1 %0,%1":"=r"(result):"f"(n));return result;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Transform(const M3&m,qword p){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(p):"j"(m.row[0].q),"j"(m.row[1].q),"j"(m.row[2].q));return p;}
static inline qword Broadcast(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword a,qword scalar){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(scalar));return r;}
static inline float XY(qword a){qword r;float f;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(r));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
static inline float Dot(qword a,qword b){qword d,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
extern "C" ENTRY*func_00173F18(SET*set,qword point,qword*outPoint,M3*outBasis,int*outFlip){
 WORK w;
 w.input.q=point;w.query.outPoint=outPoint;w.query.outBasis=outBasis;w.query.outFlip=outFlip;
 register float smallestRadius __asm__("$f21")=D_002A53E0;
 {int remaining=set->radiusCount;P**objects=set->radiusObjects;
  for(;remaining>0;remaining--,objects++)smallestRadius=Min((*objects)->radius,smallestRadius);
 }
 w.query.flip=0;
 func_001AE478(&w.heap);
 func_001B44D8(&w.query.count,&w.query.objects);
 w.query.selected=0;
 register float bestDistance __asm__("$f22")=D_002A53E0;
 register int i __asm__("$16");
 for(i=0;i<set->count;i=w.next){
  ENTRY*entry=&set->entries[i];
  w.next=i+1;
  if(entry->busy)continue;
  if(D_002DDED0<entry->until)continue;
  P*object=entry->object;
  if(!object||!((object->flags>>60)&1))continue;
  switch(entry->kind){
  case 0:case 2:{
   float radius;
   if(entry->kind==0){
    w.candidate.q=func_001A62E8(entry->object);
    M4*m=func_001A6318(entry->object);
    w.scratch.basis.row[0]=m->row[0];w.scratch.basis.row[1]=m->row[1];w.scratch.basis.row[2]=m->row[2];
    radius=entry->object->radius;
   }else if(entry->kind==2){
    radius=smallestRadius;
    w.candidate.q=func_001A62E8(entry->object);
    M4*m=func_001A6318(entry->object);
    w.scratch.basis.row[0]=m->row[0];w.scratch.basis.row[1]=m->row[1];w.scratch.basis.row[2]=m->row[2];
   }
   float distance=XY(Sub(w.input.q,w.candidate.q));
   if(distance<D_002BE5E4||bestDistance<distance)continue;
   int j;
   for(j=0;j<set->pointCount;j++)
    if(!func_00173768(set,Add(w.candidate.q,Transform(*(M3*)&w.scratch.basis,set->points[j])),w.query.count,w.query.objects,radius))goto next_entry;
   bestDistance=distance;w.query.selected=entry;w.bestPoint=w.candidate;w.bestBasis=*(M3*)&w.scratch.basis;
   break;
  }
  case 1:{
   int samples=Nearest(func_001E6648(object)/D_002BE5E8);
   int j;
   for(j=0;j<samples;j++){
    float distance=D_002BE5E8*((float)j+func_0011D448(D_002BBB60.low,D_002BBB60.high));
    if(func_001EA3B0(object->blocked,distance))continue;
    func_001E6F10(object,&w.scratch.sample.position.q,&w.scratch.sample.direction.q,distance);
    distance=XY(Sub(w.input.q,w.scratch.sample.position.q));
    if(distance<D_002BE5E4||bestDistance<distance)continue;
    bool opposite=Dot(D_002DDF40.direction,w.scratch.sample.direction.q)<0.0f;
    if(!opposite){w.scratch.sample.scalar.q=Broadcast(-1.0f);w.scratch.sample.direction.q=Scale(w.scratch.sample.direction.q,w.scratch.sample.scalar.q);}
    float angle=func_002458F0(w.scratch.sample.direction.f[1],w.scratch.sample.direction.f[0]);
    new(&w.rotation) M3(func_0011B500(D_002A2DC0,angle));
    int k;
    for(k=0;k<set->pointCount;k++)
     if(!func_00173768(set,Add(w.scratch.sample.position.q,Transform(w.rotation,set->points[k])),w.query.count,w.query.objects,smallestRadius))break;
    if(k>=set->pointCount){
     bestDistance=distance;w.query.flip=opposite;w.query.selected=entry;w.bestPoint=w.scratch.sample.position;w.bestBasis=w.rotation;
    }
   }
   break;
  }
  default:break;
  }
 next_entry:;
 }
 *w.query.outPoint=w.bestPoint.q;
 *w.query.outBasis=w.bestBasis;
 *w.query.outFlip=w.query.flip;
 func_001AE4A0(&w.heap,2);
 return w.query.selected;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char UnsignedLong_Size[(sizeof(unsigned long)==8)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(M3)==0x30)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char ROWS_Size[(sizeof(ROWS)==0x30)?1:-1];
typedef char SAMPLE_Size[(sizeof(SAMPLE)==0x30)?1:-1];
typedef char SCRATCH_Size[(sizeof(SCRATCH)==0x30)?1:-1];
typedef char HEAP_Size[(sizeof(HEAP)==1)?1:-1];
typedef char QUERY_Size[(sizeof(QUERY)==0x1C)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x100)?1:-1];
typedef char ENTRY_Size[(sizeof(ENTRY)==0x1C)?1:-1];
typedef char SET_Size[(sizeof(SET)==0xA0)?1:-1];
typedef char LM_Size[(sizeof(LM)==8)?1:-1];
typedef char LM_low_Offset[((unsigned)&((LM*)0)->low==0)?1:-1];
typedef char LM_high_Offset[((unsigned)&((LM*)0)->high==4)?1:-1];
typedef char P_flags_Offset[((unsigned)&((P*)0)->flags==40)?1:-1];
typedef char P_radius_Offset[((unsigned)&((P*)0)->radius==56)?1:-1];
typedef char P_blocked_Offset[((unsigned)&((P*)0)->blocked==384)?1:-1];
typedef char ENTRY_kind_Offset[((unsigned)&((ENTRY*)0)->kind==0)?1:-1];
typedef char ENTRY_object_Offset[((unsigned)&((ENTRY*)0)->object==8)?1:-1];
typedef char ENTRY_busy_Offset[((unsigned)&((ENTRY*)0)->busy==20)?1:-1];
typedef char ENTRY_until_Offset[((unsigned)&((ENTRY*)0)->until==24)?1:-1];
typedef char SET_count_Offset[((unsigned)&((SET*)0)->count==80)?1:-1];
typedef char SET_entries_Offset[((unsigned)&((SET*)0)->entries==84)?1:-1];
typedef char SET_radiusCount_Offset[((unsigned)&((SET*)0)->radiusCount==144)?1:-1];
typedef char SET_radiusObjects_Offset[((unsigned)&((SET*)0)->radiusObjects==148)?1:-1];
typedef char SET_pointCount_Offset[((unsigned)&((SET*)0)->pointCount==152)?1:-1];
typedef char SET_points_Offset[((unsigned)&((SET*)0)->points==156)?1:-1];
typedef char CAMERA_direction_Offset[((unsigned)&((CAMERA*)0)->direction==96)?1:-1];
typedef char QUERY_count_Offset[((unsigned)&((QUERY*)0)->count==0)?1:-1];
typedef char QUERY_objects_Offset[((unsigned)&((QUERY*)0)->objects==4)?1:-1];
typedef char QUERY_outPoint_Offset[((unsigned)&((QUERY*)0)->outPoint==8)?1:-1];
typedef char QUERY_outBasis_Offset[((unsigned)&((QUERY*)0)->outBasis==12)?1:-1];
typedef char QUERY_outFlip_Offset[((unsigned)&((QUERY*)0)->outFlip==16)?1:-1];
typedef char QUERY_selected_Offset[((unsigned)&((QUERY*)0)->selected==20)?1:-1];
typedef char QUERY_flip_Offset[((unsigned)&((QUERY*)0)->flip==24)?1:-1];
typedef char SAMPLE_position_Offset[((unsigned)&((SAMPLE*)0)->position==0)?1:-1];
typedef char SAMPLE_direction_Offset[((unsigned)&((SAMPLE*)0)->direction==16)?1:-1];
typedef char SAMPLE_scalar_Offset[((unsigned)&((SAMPLE*)0)->scalar==32)?1:-1];
typedef char WORK_heap_Offset[((unsigned)&((WORK*)0)->heap==0)?1:-1];
typedef char WORK_bestPoint_Offset[((unsigned)&((WORK*)0)->bestPoint==16)?1:-1];
typedef char WORK_bestBasis_Offset[((unsigned)&((WORK*)0)->bestBasis==32)?1:-1];
typedef char WORK_scratch_Offset[((unsigned)&((WORK*)0)->scratch==80)?1:-1];
typedef char WORK_rotation_Offset[((unsigned)&((WORK*)0)->rotation==128)?1:-1];
typedef char WORK_query_Offset[((unsigned)&((WORK*)0)->query==176)?1:-1];
typedef char WORK_candidate_Offset[((unsigned)&((WORK*)0)->candidate==208)?1:-1];
typedef char WORK_input_Offset[((unsigned)&((WORK*)0)->input==224)?1:-1];
typedef char WORK_next_Offset[((unsigned)&((WORK*)0)->next==240)?1:-1];
