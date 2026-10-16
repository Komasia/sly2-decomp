typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];int i[4];};struct P;
struct CONTACT{char pad0[8];P*owner;char padC[0x80-12];U normal;char pad90[0x1C];CONTACT*next;};
struct GROUP{CONTACT*first;GROUP*next;};struct COLLISION{char pad0[0x64];GROUP*groups;CONTACT*single;};struct P{char pad0[0xEC];COLLISION*collision;};struct MOVE{P*actor;char pad4[0x18];int mode;};
struct FRAME{};struct REQ{int bytes,alignment;};union SCRATCH{U scalar;REQ request;};struct WORK{U normals[64];SCRATCH scratch;FRAME frame;U residual,original;};
extern "C"{extern U D_002A2DC0;extern float D_002A63B0;FRAME*func_001AE478(FRAME*);void func_001AE4A0(FRAME*,int);void*func_001AE318(REQ*);void func_0011AD30(int,float*,float*,float*,float);void func_00195FB8(MOVE*,int,void*);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword ReadScalar(float*source){int bits;qword q;__asm__("lw %0,%1":"=r"(bits):"m"(*source));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Read(U*source){qword q;__asm__("lq %0,%1":"=r"(q):"m"(source->q));return q;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%1,%2x":"=j"(v):"j"(v),"j"(k));return v;}
static inline qword Vector(qword q){qword value;__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(q));return value;}
static inline float Z(qword q){float f;__asm__("qmfc2.ni %0,%1":"=r"(q):"j"(q));__asm__("pextuw %0,$zero,%0":"+r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Reject(qword value,qword up){qword q,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(q),"=&j"(one):"j"(value),"j"(up));__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(up),"j"(q));__asm__("vsub.xyzw %0,%0,%1":"+j"(value):"j"(q));return value;}
static inline void MatrixDot(float*out,qword a,qword b){qword q=a,one;int bits;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(q),"=&j"(one):"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("sw %1,%0":"=m"(*out):"r"(bits));}
static inline void VectorDot(float*out,qword a,qword b){qword q=b,one;int bits;__asm__("vmul.xyz %0,%2,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(q),"=&j"(one):"j"(a));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("sw %1,%0":"=m"(*out):"r"(bits));}
static inline qword AddScaled(qword sum,qword normal,qword k){__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(sum):"j"(sum),"j"(normal),"j"(k));return sum;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Square(qword a){qword q=a,one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(q),"=&j"(one));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline float*Allocate(REQ*r,int bytes){r->bytes=bytes;r->alignment=16;return(float*)func_001AE318(r);}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char CONTACT_Size[sizeof(CONTACT)==176?1:-1];
typedef char GROUP_Size[sizeof(GROUP)==8?1:-1];
typedef char COLLISION_Size[sizeof(COLLISION)==108?1:-1];
typedef char P_Size[sizeof(P)==240?1:-1];
typedef char MOVE_Size[sizeof(MOVE)==32?1:-1];
typedef char FRAME_Size[sizeof(FRAME)==1?1:-1];
typedef char REQ_Size[sizeof(REQ)==8?1:-1];
typedef char SCRATCH_Size[sizeof(SCRATCH)==16?1:-1];
typedef char WORK_Size[sizeof(WORK)==1088?1:-1];
typedef char CONTACT_owner_Offset[FIELD_OFFSET(CONTACT,owner)==8?1:-1];
typedef char CONTACT_normal_Offset[FIELD_OFFSET(CONTACT,normal)==128?1:-1];
typedef char CONTACT_next_Offset[FIELD_OFFSET(CONTACT,next)==172?1:-1];
typedef char GROUP_first_Offset[FIELD_OFFSET(GROUP,first)==0?1:-1];
typedef char GROUP_next_Offset[FIELD_OFFSET(GROUP,next)==4?1:-1];
typedef char COLLISION_groups_Offset[FIELD_OFFSET(COLLISION,groups)==100?1:-1];
typedef char COLLISION_single_Offset[FIELD_OFFSET(COLLISION,single)==104?1:-1];
typedef char P_collision_Offset[FIELD_OFFSET(P,collision)==236?1:-1];
typedef char MOVE_actor_Offset[FIELD_OFFSET(MOVE,actor)==0?1:-1];
typedef char MOVE_mode_Offset[FIELD_OFFSET(MOVE,mode)==28?1:-1];
typedef char REQ_bytes_Offset[FIELD_OFFSET(REQ,bytes)==0?1:-1];
typedef char REQ_alignment_Offset[FIELD_OFFSET(REQ,alignment)==4?1:-1];
typedef char WORK_normals_Offset[FIELD_OFFSET(WORK,normals)==0?1:-1];
typedef char WORK_scratch_Offset[FIELD_OFFSET(WORK,scratch)==1024?1:-1];
typedef char WORK_frame_Offset[FIELD_OFFSET(WORK,frame)==1040?1:-1];
typedef char WORK_residual_Offset[FIELD_OFFSET(WORK,residual)==1056?1:-1];
typedef char WORK_original_Offset[FIELD_OFFSET(WORK,original)==1072?1:-1];
extern "C" void func_00196AA8(MOVE*p,U*out){
 WORK w;int count=0;CONTACT*c;GROUP*group=p->actor->collision->groups;
 for(;;){c=group?group->first:p->actor->collision->single;
  if(c){do{if((uint)count>=64)break;qword normal=c->normal.q;if(p->actor!=c->owner){w.scratch.scalar.q=Scalar(-1.0f);normal=Scale(normal,w.scratch.scalar.q);}if(Z(normal)>0.7f)continue;w.normals[count].q=Reject(normal,D_002A2DC0.q);count++;}while((c=c->next)!=0);}
  if(!group)break;group=group->next;
 }
 if(!count)return;
 (void)func_001AE478(&w.frame);
 float*matrix=Allocate(&w.scratch.request,count*count*4);float*rhs=Allocate(&w.scratch.request,count*4);float*weights=Allocate(&w.scratch.request,count*4);
 float*cursor=matrix;
 for(int i=0;i<count;i++){for(int j=0;j<count;j++){MatrixDot(cursor,w.normals[i].q,w.normals[j].q);cursor++;}}
 qword original=Read(out);w.residual.q=original;w.original.q=original;
 if(count>0){float*write=rhs;U*normal=w.normals;for(int remaining=count;remaining!=0;remaining--){VectorDot(write,Vector(original),normal->q);write++;normal++;}}
 func_0011AD30(count,matrix,rhs,weights,D_002A63B0);
 if(count>0){float*read=weights;U*normal=w.normals;for(int remaining=count;remaining!=0;remaining--){w.scratch.scalar.q=ReadScalar(read);w.residual.q=AddScaled(w.residual.q,normal->q,w.scratch.scalar.q);read++;normal++;}}
 if(Square(Sub(w.original.q,w.residual.q))>1.0f){switch(p->mode){case 0:func_00195FB8(p,1,0);break;case 2:func_00195FB8(p,3,0);break;}}
 *out=w.residual;func_001AE4A0(&w.frame,2);
}