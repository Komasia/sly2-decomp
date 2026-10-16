typedef int qword __attribute__((mode(TI)));
struct M3{qword r[3];};
struct M4{qword r[4];};
struct PLANE{qword normal;int unknown10,unknown14,unknown18,vertex;};
struct GEOMETRY{int pointCount;qword*points;int planeCount;PLANE*planes;};
extern "C" void func_00166428(const M4*,unsigned int,const qword*,qword*);
extern "C" M3 func_0011B340(const M3*);
static __inline__ qword PextLW(qword a,qword b){qword v;__asm__("pextlw %0,%1,%2":"=r"(v):"r"(a),"r"(b));return v;}
static __inline__ qword PextUW(qword a,qword b){qword v;__asm__("pextuw %0,%1,%2":"=r"(v):"r"(a),"r"(b));return v;}
static __inline__ qword CopyLD(qword a,qword b){qword v;__asm__("pcpyld %0,%1,%2":"=r"(v):"r"(a),"r"(b));return v;}
static __inline__ qword CopyUD(qword a,qword b){qword v;__asm__("pcpyud %0,%1,%2":"=r"(v):"r"(a),"r"(b));return v;}
static __inline__ qword ReadCPU(const qword*source){qword value;__asm__("lq %0,%1":"=r"(value):"m"(*source));return value;}
static __inline__ qword ZeroPextLW(qword input){qword v;__asm__("pextlw %0,$zero,%1":"=r"(v):"r"(input));return v;}
static __inline__ qword ZeroPextUW(qword input){qword v;__asm__("pextuw %0,$zero,%1":"=r"(v):"r"(input));return v;}
static __inline__ M3 Transpose(const M3&input){
 M3 out;
 qword xy=PextLW(input.r[1],input.r[0]);
 qword zw=PextUW(input.r[1],input.r[0]);
 qword cx=ZeroPextLW(input.r[2]);
 qword cz=ZeroPextUW(input.r[2]);
 out.r[0]=CopyLD(cx,xy);out.r[1]=CopyUD(xy,cx);out.r[2]=CopyLD(cz,zw);
 return out;
}
extern "C" void func_001664A0(const M4*matrix,GEOMETRY*source,GEOMETRY*dest){
 if(source->points!=dest->points){
  func_00166428(matrix,source->pointCount,source->points,dest->points);
  M3 normal;normal=Transpose(func_0011B340((const M3*)matrix));
  if(source->planeCount>0){
   PLANE*input=source->planes;PLANE*output=dest->planes;PLANE*last=output+source->planeCount-1;
   qword nextNormal,nextAnchor;
   register qword v1 __asm__("vf1")=normal.r[0],v2 __asm__("vf2")=normal.r[1],v3 __asm__("vf3")=normal.r[2];
   register qword v4 __asm__("vf4")=dest->points[input->vertex],v5 __asm__("vf5")=input->normal;
   input++;
   for(;;){
    __asm__ __volatile__("vcallms 0x150" : : "j"(v1),"j"(v2),"j"(v3),"j"(v4),"j"(v5));
    if(output<last){
     int vertex=input->vertex;
     nextNormal=ReadCPU(&input->normal);nextAnchor=ReadCPU(&dest->points[vertex]);input++;
    }
    {
     int sync;register qword result __asm__("vf5");
     __asm__ __volatile__("cfc2.i %0,$vi0":"=r"(sync),"=j"(result) : : "vf6","vf7","vf8");
     output->normal=result;
    }
    if(output==last)break;
    v4=nextAnchor;v5=nextNormal;output++;
   }
  }
 }
}

typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_M3[(sizeof(M3)==0x30)?1:-1];
typedef char layout_M3_alignment[(__alignof__(M3)==16)?1:-1];
typedef char layout_M4[(sizeof(M4)==0x40)?1:-1];
typedef char layout_PLANE[(sizeof(PLANE)==0x20)?1:-1];
typedef char layout_GEOMETRY[(sizeof(GEOMETRY)==0x10)?1:-1];
typedef char layout_GEOMETRY_pointCount[((unsigned long)&((GEOMETRY*)0)->pointCount==0x0)?1:-1];
typedef char layout_GEOMETRY_points[((unsigned long)&((GEOMETRY*)0)->points==0x4)?1:-1];
typedef char layout_GEOMETRY_planeCount[((unsigned long)&((GEOMETRY*)0)->planeCount==0x8)?1:-1];
typedef char layout_GEOMETRY_planes[((unsigned long)&((GEOMETRY*)0)->planes==0xc)?1:-1];
typedef char layout_PLANE_normal[((unsigned long)&((PLANE*)0)->normal==0x0)?1:-1];
typedef char layout_PLANE_vertex[((unsigned long)&((PLANE*)0)->vertex==0x1c)?1:-1];
typedef char layout_M3_row0[((unsigned long)&((M3*)0)->r[0]==0x0)?1:-1];
typedef char layout_M3_row1[((unsigned long)&((M3*)0)->r[1]==0x10)?1:-1];
typedef char layout_M3_row2[((unsigned long)&((M3*)0)->r[2]==0x20)?1:-1];
