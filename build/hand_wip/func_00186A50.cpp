
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct M3{
 U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}
 M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return*this;}
};
struct M4{U r[4];};
struct FRAME{M4 local,world;char pad80[0x20];FRAME*parent;int stamp;};
struct VTE{short delta,pad;void*fn;};struct CONTROL{VTE*vt;};
struct REQUEST{
 FRAME*primary,*current,*output,*ancestor;M4 snapshot;M3 rest;
 qword translation,axis,localPoint,mappedPoint;float firstLength,secondLength,referenceAngle,twist;
 CONTROL*control;float*parameters;
};
struct GAME{char pad[0x3D58];int stamp;};extern "C" GAME D_003DD490;
extern "C" float func_002456F0(float);
extern "C" M3 func_0011B500(qword,float);
extern "C" qword*func_00256D18(qword*,qword);
extern "C" float func_0011E4B0(qword,qword,qword*);
extern "C" qword func_0022FCC8(void*,void*,qword);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword PointFresh(const M4&m,qword p){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(p));return r;}
static inline qword PointInput(const M4&m,qword p){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(p):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q));return p;}
static inline qword PointRow0(const M4&m,qword p){qword r=m.r[0].q;__asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(p));return r;}
static inline void CopySnapshot(REQUEST*q){FRAME*d=q->current;d->local.r[0]=q->snapshot.r[0];d->local.r[1]=q->snapshot.r[1];d->local.r[2]=q->snapshot.r[2];d->local.r[3]=q->snapshot.r[3];}

static inline qword ReadQ(const qword*p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline float Length(qword a){qword d,one;float length;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(length):"j"(d));return length;}
static inline qword Unit(qword a){qword d,one,root,r;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(root):"j"(d));__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(root),"j"(a));return r;}
static inline void Build(M4&d,const M3&m,qword p){func_00256D18(&d.r[3].q,p);d.r[0]=m.r[0];d.r[1]=m.r[1];d.r[2]=m.r[2];d.r[3].f[3]=1.0f;d.r[0].i[3]=d.r[1].i[3]=d.r[2].i[3]=0;}
static inline M3 Mul(const M3&a,const M3&b) return r{
 qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
extern "C" void func_00186A50(void*context,REQUEST*q){
 qword base,delta;M3*originalBasis;
 CopySnapshot(q);
 base=PointFresh(q->current->parent->world,q->snapshot.r[3].q);
 delta=Sub(PointRow0(q->primary->world,q->localPoint),base);
 {float length=Length(ReadQ(&delta));float a=q->firstLength,b=q->secondLength;
  float cosine=((length*length)-(a*a)-(b*b))/((a+a)*b);
  register float low __asm__("$f5")=-1.0f;register float high __asm__("$f6")=1.0f;
  if(cosine<low)cosine=low;else if(high<cosine)cosine=high;
  originalBasis=(M3*)&q->snapshot;float angle=func_002456F0(cosine);
  M3 rotation=func_0011B500(q->axis,angle-q->referenceAngle);
  M3 oriented=Mul(rotation,q->rest);
  Build(q->output->local,oriented,q->translation);
 }
 qword transported=q->mappedPoint;
 for(FRAME*f=q->ancestor;f!=q->current->parent;f=f->parent)transported=PointInput(f->local,transported);
 U axis;
 float angle=func_0011E4B0(Sub(PointInput(q->current->parent->world,transported),base),delta,&axis.q);
 axis.q=func_0022FCC8(0,q->current->parent,axis.q);
 M3 aligned;
 aligned=func_0011B500(Unit(axis.q),angle);
 if(q->control){CONTROL*c=q->control;VTE*e=&c->vt[2];((void(*)(void*,float*,int,float,float))e->fn)((char*)c+e->delta,&q->twist,0,q->parameters[0],0.0f);}
 qword turnAxis=Unit(func_0022FCC8(0,q->current->parent,delta));
 M3 twisted=func_0011B500(turnAxis,q->twist);
 M3 combined=Mul(twisted,aligned);
 M3 updated=Mul(combined,*originalBasis);
 FRAME*current=q->current;current->local.r[0]=updated.r[0];current->local.r[1]=updated.r[1];current->local.r[2]=updated.r[2];
 current->local.r[0].i[3]=current->local.r[1].i[3]=current->local.r[2].i[3]=0;
 int stamp=++D_003DD490.stamp;
 q->current->stamp=stamp;q->output->stamp=stamp;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(M3)==0x30)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char REQUEST_Size[(sizeof(REQUEST)==0xE0)?1:-1];
typedef char FRAME_Size[(sizeof(FRAME)==0xB0)?1:-1];
typedef char FRAME_local_Offset[((unsigned)&((FRAME*)0)->local==0)?1:-1];
typedef char FRAME_world_Offset[((unsigned)&((FRAME*)0)->world==64)?1:-1];
typedef char FRAME_parent_Offset[((unsigned)&((FRAME*)0)->parent==160)?1:-1];
typedef char FRAME_stamp_Offset[((unsigned)&((FRAME*)0)->stamp==164)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char CONTROL_vt_Offset[((unsigned)&((CONTROL*)0)->vt==0)?1:-1];
typedef char REQUEST_primary_Offset[((unsigned)&((REQUEST*)0)->primary==0)?1:-1];
typedef char REQUEST_current_Offset[((unsigned)&((REQUEST*)0)->current==4)?1:-1];
typedef char REQUEST_output_Offset[((unsigned)&((REQUEST*)0)->output==8)?1:-1];
typedef char REQUEST_ancestor_Offset[((unsigned)&((REQUEST*)0)->ancestor==12)?1:-1];
typedef char REQUEST_snapshot_Offset[((unsigned)&((REQUEST*)0)->snapshot==16)?1:-1];
typedef char REQUEST_rest_Offset[((unsigned)&((REQUEST*)0)->rest==80)?1:-1];
typedef char REQUEST_translation_Offset[((unsigned)&((REQUEST*)0)->translation==128)?1:-1];
typedef char REQUEST_axis_Offset[((unsigned)&((REQUEST*)0)->axis==144)?1:-1];
typedef char REQUEST_localPoint_Offset[((unsigned)&((REQUEST*)0)->localPoint==160)?1:-1];
typedef char REQUEST_mappedPoint_Offset[((unsigned)&((REQUEST*)0)->mappedPoint==176)?1:-1];
typedef char REQUEST_firstLength_Offset[((unsigned)&((REQUEST*)0)->firstLength==192)?1:-1];
typedef char REQUEST_secondLength_Offset[((unsigned)&((REQUEST*)0)->secondLength==196)?1:-1];
typedef char REQUEST_referenceAngle_Offset[((unsigned)&((REQUEST*)0)->referenceAngle==200)?1:-1];
typedef char REQUEST_twist_Offset[((unsigned)&((REQUEST*)0)->twist==204)?1:-1];
typedef char REQUEST_control_Offset[((unsigned)&((REQUEST*)0)->control==208)?1:-1];
typedef char REQUEST_parameters_Offset[((unsigned)&((REQUEST*)0)->parameters==212)?1:-1];
typedef char GAME_stamp_Offset[((unsigned)&((GAME*)0)->stamp==15704)?1:-1];
