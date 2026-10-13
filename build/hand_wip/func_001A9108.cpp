
typedef int qword __attribute__((mode(TI)));
struct FRAME{int pad[4];};
struct REQ{int cb,kind;};
struct POLY{qword plane;int x10,x14,flags;};
struct ENTRY{int x0,x4;POLY*poly;};
struct HIT{qword p;char pad10[0x30];float time;char pad44[0x1C];};
struct OUT{qword p,plane;int kind;};
union U{qword q;float f[4];};union SCR{REQ req;U u;};
extern "C" FRAME*func_001AE478(FRAME*);
extern "C" void func_001AE4A0(FRAME*,int);
extern "C" void*func_001AE318(REQ*);
extern "C" int func_00118A88(void*,int,qword,float,int*,ENTRY**);
extern "C" int func_00118668(void*,int,qword,qword,int,HIT*);
extern "C" void func_00119390(qword*,qword,qword);
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword AddScaled(qword a,qword b,float f,U*u){qword x,r;__asm__("qmtc2.ni %1,%0":"=j"(x):"r"(f));u->q=x;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(x));return r;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Normal(qword v){register qword d __asm__("vf2"),one __asm__("vf3"),r __asm__("vf3");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(d),"j"(v));return r;}
extern "C" void func_001A9108(void*tree,int mask,int unused,qword pos,OUT*out,float radius0){
 FRAME frame;SCR scratch;
 float radius=Max(radius0,100.0f);
 func_001AE478(&frame);
 ENTRY*first;
 {REQ*r=&scratch.req;r->cb=0xFFFC;r->kind=16;first=(ENTRY*)func_001AE318(r);}
 HIT hits[16];int count;ENTRY*end;int limit=0x1555;
 if(radius<52000.0f)do {
  end=first;count=limit;
  int status=func_00118A88(tree,mask,pos,radius,&count,&end);
  if(status<0)break;
  if(status<2)goto more;
  if(status!=2)goto more;
  {count=end-first;
  float best=0.0f;
  int i;
  for(i=0;i<count;i++){
   register POLY*poly __asm__("$6")=first[i].poly;
   if(poly->flags&0x1000)continue;
   poly->flags|=0x1000;
   qword to=AddScaled(pos,poly->plane,radius+1.0f,&scratch.u);
   if(func_00118668(end-1,0x7FFFFFFF,to,pos,16,hits)>0){
    if(hits[0].time>best){
     best=hits[0].time;
     qword normal=Normal(Sub(to,pos));
     out->p=hits[0].p;
     func_00119390(&out->plane,normal,hits[0].p);
     out->kind=12;
    }
   }
  }
  for(int j=0;j<count;j++)first[j].poly->flags&=~0x1000;
  if(best>0.0f){func_001AE4A0(&frame,2);return;}
 }
 more:radius+=radius;
 }while(radius<52000.0f);
 func_001AE4A0(&frame,2);
}
