// v2 (Claude agent): aligned 10 (was 12): Z() does pextuw+mtc1 in one asm on the qword bits (mtc1-from-qword idea), fixing the v0/v1 and f0/f1 swaps at the end. Left: 0x19A174 block, target loads D_002A2DC0 (lqc2) after the work.scalar sqc2; ours hoists it.
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct P;
struct CONTACT{char pad[8];P*owner;char padC[0x74];qword normal;char pad90[0x1C];CONTACT*next;};
struct LINK{CONTACT*first;LINK*next;};
struct COLLISION{char pad[0x64];LINK*groups;};
struct P{char pad[0xEC];COLLISION*collision;char padF0[0x118];int mode;};
struct CLOCK{float time,delta;};
struct REQUEST{int bytes,alignment;};
union WORK{REQUEST request;U scalar;};
extern "C"{
extern CLOCK D_002DDED0;
extern qword D_002A2DC0;
extern float D_002A656C;
void*func_001AE478(void*);
void func_001AE4A0(void*,int);
void*func_001AE318(REQUEST*);
void func_0011AD30(int,float*,float*,float*,float);
}
struct MARK{MARK(){func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Scale(qword v,qword k){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(v),"j"(k));return q;}
static inline qword ScaleNew(qword v,qword k){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(q):"j"(v),"j"(k));return q;}
static inline qword Copy(qword v){qword q;__asm__("vmove.xyzw %0,%1":"=j"(q):"j"(v));return q;}
static inline qword Normal(P*p,CONTACT*c,WORK*work){qword normal=c->normal;if(c->owner!=p){qword minus=Scalar(-1.0f);work->scalar.q=minus;normal=Scale(normal,work->scalar.q);}return normal;}
static inline void StoreDot(float*out,qword a,qword b){register qword product __asm__("vf1"),one __asm__("vf2");int bits;__asm__("vmul.xyz %1,%4,%5\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%2,%1z\n\tqmfc2.ni %0,%1\n\tsw %0,%3":"=&r"(bits),"=&j"(product),"=j"(one),"=m"(*out):"j"(a),"j"(b));}
static inline qword AddScaled(qword sum,qword normal,float weight,WORK*work){work->scalar.q=Scalar(weight);__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(sum):"j"(sum),"j"(normal),"j"(work->scalar.q));return sum;}
static inline float Z(qword q){qword bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("pextuw %1,$zero,%1\n\tmtc1 %1,%0":"=f"(f),"+r"(bits));return f;}
static inline float*Allocate(REQUEST*request,int bytes){request->bytes=bytes;request->alignment=16;return (float*)func_001AE318(request);}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char CONTACT_Size[sizeof(CONTACT)==176?1:-1];
typedef char LINK_Size[sizeof(LINK)==8?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char REQUEST_Size[sizeof(REQUEST)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==16?1:-1];
typedef char CONTACT_owner_Offset[FIELD_OFFSET(CONTACT,owner)==8?1:-1];
typedef char CONTACT_normal_Offset[FIELD_OFFSET(CONTACT,normal)==128?1:-1];
typedef char CONTACT_next_Offset[FIELD_OFFSET(CONTACT,next)==172?1:-1];
typedef char LINK_first_Offset[FIELD_OFFSET(LINK,first)==0?1:-1];
typedef char LINK_next_Offset[FIELD_OFFSET(LINK,next)==4?1:-1];
typedef char COLLISION_groups_Offset[FIELD_OFFSET(COLLISION,groups)==100?1:-1];
typedef char P_collision_Offset[FIELD_OFFSET(P,collision)==236?1:-1];
typedef char P_mode_Offset[FIELD_OFFSET(P,mode)==520?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char REQUEST_bytes_Offset[FIELD_OFFSET(REQUEST,bytes)==0?1:-1];
typedef char REQUEST_alignment_Offset[FIELD_OFFSET(REQUEST,alignment)==4?1:-1];
extern "C" int func_0019A098(P*p,float previous,float*stamp){
 float now=D_002DDED0.time;
 if(now-previous<1.0f)return 0;
 if(stamp){if(now-*stamp<1.0f)return 0;*stamp=now;}
 if(p->mode)return 0;
 int count=0;LINK*group;CONTACT*c;
 for(group=p->collision->groups;group;group=group->next)for(c=group->first;c;c=c->next)count++;
 if(!count)return 0;
 MARK arena;
 WORK work;
 work.scalar.q=Scalar(-1.0f);
 U down;down.q=ScaleNew(D_002A2DC0,work.scalar.q);
 float*matrix=Allocate(&work.request,count*count*4);
 float*rhs=Allocate(&work.request,count*4);
 float*weights=Allocate(&work.request,count*4);
 float*cursor=matrix;
 for(group=p->collision->groups;group;group=group->next){
  for(c=group->first;c;c=c->next){
   qword normal=Normal(p,c,&work);
   for(LINK*other=p->collision->groups;other;other=other->next){
    CONTACT*d=other->first;if(!d)continue;
    qword current=Copy(normal);
    do{StoreDot(cursor,current,Normal(p,d,&work));cursor++;}while((d=d->next)!=0);
   }
  }
 }
 cursor=rhs;
 for(group=p->collision->groups;group;group=group->next){c=group->first;if(!c)continue;qword downvalue=down.q;do{StoreDot(cursor,Normal(p,c,&work),downvalue);cursor++;}while((c=c->next)!=0);}
 func_0011AD30(count,matrix,rhs,weights,D_002A656C);
 qword sum=down.q;
 cursor=weights;
 for(group=p->collision->groups;group;group=group->next){c=group->first;if(!c)continue;do{qword normal=Normal(p,c,&work);float weight=*cursor;c=c->next;cursor++;sum=AddScaled(sum,normal,weight,&work);}while(c);}
 float z=Z(sum);int result=1;if(-0.1f<z){}else result=0;return result;
}
