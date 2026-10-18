typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;typedef unsigned long ulong;
union U{qword q;float f[4];uint u[4];};
union WORD{int bits;float value;};
struct M4{U r[4];};struct M3{U r[3];};
struct V3{float x,y,z;};struct SPHERE{V3 center;float radius;};
struct LOCAL_SPHERE{SPHERE sphere;float range;int unknown;};
struct VTE{short delta,pad;void*fn;};
struct T{char pad0[0x40];M4 matrix;};
struct BONE{int value;float unknown;short index,padA;T*transform;M4 matrix;};
struct SKIN{char pad0[0xC];char*owner;int count,first,second;int pad1C;uint base;};
struct D{signed char kind,count;short channel;float distance;void*chain;uint base,words;};
struct E{int unknown;T*transform;M4*parent;uint flags;char*data;uint word;BONE*bones;SKIN*skin;int pad20;SPHERE*sphere;};
union FLAGS{ulong bits;struct{float scale;uint upper;}raw;};
struct NODE{char pad0[0xC];VTE*vt;char pad10[0x28];WORD range;char pad3C[0x24];T*frame;};
struct P{NODE*owner;float stamp;char pad8[8];U center;float radius;int objectCount;NODE**objects;int pad2C,pad30;uint mode;int count;D*descriptors;E*entries;LOCAL_SPHERE*spheres;int pad48,stampId;FLAGS flags;};
struct SHADER{uint words[9];M4*clip;uint reference,size;};
struct ENV{char pad0[0x1C];WORD gain;char pad20[0x28];float near;char pad4C[0x44];U camera;M3 planes;};
struct GAME{char pad0[0x3BEC];int alternate;char pad3BF0[0x16C];int stamp;};
struct CLOCK{float time,dt;};struct R{char pad0[0xC];unsigned char*cur;};
struct Q{int kind;float distance;unsigned char*start;char*data;};
struct MATRICES{M4 source,product,skin,skinProduct;};
struct SKIN_WORK{U parameters;M4 inverse;};union TMP{MATRICES matrices;SKIN_WORK skin;};
extern "C"{
extern ENV D_002DDF40;extern CLOCK D_002DDED0;extern GAME D_003DD490;extern R D_002DEA28;extern M4 D_002A2D30;
void func_001681F8(P*);int func_001EDA20(NODE*);
void func_001AE5A0(void*,const void*,uint);void*func_0023320C(void*,const void*,uint);
M4*func_0011C168(M4*,const M4*,const M4*);M4*func_0011C318(M4*,const M4*);
float func_0011CAB0(const M4*);qword func_00167DA0(const M4*,qword,float*);
int func_0014F898(ENV*,qword,float,float*);
void func_001684D0(P*,D*,E*);Q*func_001CD998(void);
}
static __inline__ qword ScalarBits(int bits){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(bits));return v;}
static __inline__ qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ qword InitialXYZ(const M4&m,qword source,qword result){
 register qword r __asm__("vf5")=result;
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(source));return r;
}
static __inline__ qword SphereXYZ(const M4&m,const U&source){
 register qword point __asm__("vf5")=source.q;
 register qword x __asm__("vf4")=m.r[0].q;
 register qword y __asm__("vf3")=m.r[1].q;
 register qword z __asm__("vf2")=m.r[2].q;
 register qword r __asm__("vf1")=m.r[3].q;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddaz.xyz $ACC,%3,%4z\n\tvmaddw.xyz %0,%0,$vf0w":"+j"(r):"j"(x),"j"(y),"j"(z),"j"(point));
 return r;
}
static __inline__ float X(qword v){int bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(v));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static __inline__ int SquareBits(qword v){
 qword d,one;int bits;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));return bits;
}
static __inline__ float Cull(qword center,int radius,int range,qword camera,qword&delta){
 register qword p0 __asm__("vf10")=D_002DDF40.planes.r[0].q;
 register qword p1 __asm__("vf11")=D_002DDF40.planes.r[1].q;
 register qword p2 __asm__("vf12")=D_002DDF40.planes.r[2].q;
 register qword origin __asm__("vf13")=camera;
 register qword gain __asm__("vf14")=ScalarBits(D_002DDF40.gain.bits);
 register qword point __asm__("vf15")=center;
 register qword rad __asm__("vf16")=ScalarBits(radius);
 register qword limit __asm__("vf17")=ScalarBits(range);
 register qword difference __asm__("vf18"),rating __asm__("vf19");
 __asm__ __volatile__("vcallms 0x1C0\n\tcfc2.i $zero,$vi0":"=j"(difference),"=j"(rating):"j"(p0),"j"(p1),"j"(p2),"j"(origin),"j"(gain),"j"(point),"j"(rad),"j"(limit):"vf20","vf21","vf22","vf23","vf24","vf25");
 delta=difference;return X(rating);
}
static __inline__ float Cull(qword center,int radius,int range,qword camera){
 register qword p0 __asm__("vf10")=D_002DDF40.planes.r[0].q;
 register qword p1 __asm__("vf11")=D_002DDF40.planes.r[1].q;
 register qword p2 __asm__("vf12")=D_002DDF40.planes.r[2].q;
 register qword origin __asm__("vf13")=camera;
 register qword gain __asm__("vf14")=ScalarBits(D_002DDF40.gain.bits);
 register qword point __asm__("vf15")=center;
 register qword rad __asm__("vf16")=ScalarBits(radius);
 register qword limit __asm__("vf17")=ScalarBits(range);
 register qword rating __asm__("vf19");
 __asm__ __volatile__("vcallms 0x1C0\n\tcfc2.i $zero,$vi0":"=j"(rating):"j"(p0),"j"(p1),"j"(p2),"j"(origin),"j"(gain),"j"(point),"j"(rad),"j"(limit):"vf18","vf20","vf21","vf22","vf23","vf24","vf25");
 return X(rating);
}
static __inline__ void Update(NODE*object){VTE&e=object->vt[8];((void(*)(void*))e.fn)((char*)object+e.delta);}
static __inline__ void CopyMatrix(M4*out,const M4*src){(void)func_0023320C(out,src,64);}
static __inline__ void Word(R*r,uint value){*(uint*)r->cur=value;r->cur+=4;}
static __inline__ void CopyWords(uint*dst,const uint*src,int words){int left=words-4;do{uint a=src[0],b=src[1],c=src[2],d=src[3];src+=4;dst[0]=a;dst[1]=b;dst[2]=c;dst[3]=d;dst+=4;left-=4;}while(left>=0);}
static __inline__ void Unpack(R*r,const void*src,int words,uint opcode){Word(r,opcode);CopyWords((uint*)r->cur,(const uint*)src,words);r->cur+=words*4;}
static __inline__ void UnpackOne(R*r,const int*src,uint opcode){Word(r,opcode);int left=0;uint*dst=(uint*)r->cur;do{*dst++=*src++;left--;}while(left>=0);r->cur+=4;}
static __inline__ void Align(R*r){while((uint)r->cur&15){*(uint*)r->cur=0;r->cur+=4;}}
static __inline__ void Ref(R*r,uint address,uint count){ulong low=(ulong)(int)(address|0x40000000U);ulong high=(ulong)(int)count<<32;*(ulong*)r->cur=low|high;r->cur+=16;}
static __inline__ qword RootXYZ(const M4&m,const U&source){
 register qword r __asm__("vf5")=m.r[0].q;
 register qword last __asm__("vf4")=m.r[3].q;
 register qword y __asm__("vf3")=m.r[1].q;
 register qword z __asm__("vf2")=m.r[2].q;
 register qword point __asm__("vf1")=source.q;
 __asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(y),"j"(z),"j"(last),"j"(point));
 return r;
}
extern "C" void func_00168638(P*p,M4*optional,SHADER*shader,float first,float second){
 register float firstValue __asm__("$f22")=first;
 register float secondValue __asm__("$f21")=second;
 U input;M4 model;TMP tmp;
 float rootRadius=p->radius,radius,entryVisibility;
 int nearby;
 U camera=D_002DDF40.camera,difference,world,initial;
 int alternate,i,next;
 unsigned char*start;
 const M4&root=p->owner->frame->matrix;
 register qword center __asm__("vf5")=RootXYZ(root,p->center);
 if(optional){initial.q=InitialXYZ(*optional,center,center);rootRadius*=func_0011CAB0(optional);center=initial.q;}
 if((p->flags.bits&0x200000000UL)&&shader->clip)center=func_00167DA0(shader->clip,center,&rootRadius);
 float visibility=Cull(center,*(int*)&rootRadius,p->owner->range.bits,camera.q);
 if(visibility==0.0f)return;
 p->stamp=D_002DDED0.time;
 if(p->stampId!=D_003DD490.stamp)func_001681F8(p);
 for(i=0;i<p->objectCount;i++){
  NODE*object=p->objects[i];
  if(func_001EDA20(object))Update(object);
 }
 alternate=0;
 if(p->flags.bits&0x400000000UL)alternate=D_003DD490.alternate==0;
 for(i=0;i<p->count;i=next){
  D*descriptor=&p->descriptors[i];
  E*entry=&p->entries[i];
  LOCAL_SPHERE*sphere=&p->spheres[i];
  next=i+1;
  if(entry->flags&0x800)continue;
  if(entry->flags&0x1000){
   func_001AE5A0(&model,entry->data+0x14,64);
   if(optional){func_0011C168(&tmp.matrices.source,optional,&model);model=tmp.matrices.source;}
  }else{
   M4*parent=entry->parent;
   CopyMatrix(&tmp.matrices.source,&entry->transform->matrix);
   if(parent){func_0011C168(&tmp.matrices.product,&tmp.matrices.source,parent);CopyMatrix(&tmp.matrices.source,&tmp.matrices.product);}
   if(optional){func_0011C168(&tmp.matrices.product,optional,&tmp.matrices.source);CopyMatrix(&tmp.matrices.source,&tmp.matrices.product);}
   model=tmp.matrices.source;
  }
  func_001AE5A0(&input,&sphere->sphere.center,12);
  world.q=SphereXYZ(model,input);
  radius=func_0011CAB0(&model)*sphere->sphere.radius;
  if((entry->flags&7)==2&&shader->clip)world.q=func_00167DA0(shader->clip,world.q,&radius);
  if(!entry->bones){
   qword delta;
   entryVisibility=Cull(world.q,*(int*)&radius,*(int*)&sphere->range,camera.q,delta);
   if(entryVisibility==0.0f)continue;
   difference.q=delta;
  }else{
   difference.q=Sub(world.q,camera.q);
   if(!func_0014F898(&D_002DDF40,difference.q,sphere->range,&entryVisibility))continue;
  }
  start=D_002DEA28.cur;
  if(entry->flags&0x100)Ref(&D_002DEA28,shader->words[5],shader->words[6]);
  unsigned char*tag;
  switch(entry->flags&7){
  case 2:
   ++i;next=i;
   if(!shader->size)continue;
   Ref(&D_002DEA28,shader->reference,shader->size);
   tag=D_002DEA28.cur;*(ulong*)tag=0x10000000UL;D_002DEA28.cur+=16;
   break;
  case 3:{
   ++i;next=i;
   tag=D_002DEA28.cur;*(ulong*)tag=0x10000000UL;D_002DEA28.cur+=16;
   WORD distance;distance.bits=SquareBits(Sub(camera.q,world.q));
   float inflated=radius+D_002DDF40.near;
   nearby=distance.value<inflated*inflated;
   UnpackOne(&D_002DEA28,&nearby,0x6001C012);
   break;
  }
  default:
   ++i;next=i;
   tag=D_002DEA28.cur;*(ulong*)tag=0x10000000UL;D_002DEA28.cur+=16;
   break;
  }
  if(entry->bones){const M4*matrix=optional?optional:&D_002A2D30;Unpack(&D_002DEA28,matrix,16,0x6C04C000);}
  else Unpack(&D_002DEA28,&model,16,0x6C04C000);
  if(visibility<entryVisibility){tmp.skin.parameters.f[0]=firstValue*visibility;tmp.skin.parameters.f[1]=secondValue*visibility;}
  else{tmp.skin.parameters.f[1]=secondValue*entryVisibility;tmp.skin.parameters.f[0]=firstValue*entryVisibility;}
  tmp.skin.parameters.f[2]=p->flags.raw.scale;
  tmp.skin.parameters.u[3]=(entry->flags&0x200)?p->mode:0;
  Unpack(&D_002DEA28,&tmp.skin.parameters,4,0x6C01C008);
  if(entry->bones)func_001684D0(p,descriptor,entry);
  if(entry->skin){
   SKIN*skin=entry->skin;
   uint base=skin->base;
   func_0011C318(&tmp.skin.inverse,&model);
   for(i=0;i<skin->count;i++){
    if(skin->first){
     M4*matrix=(M4*)(skin->owner+0x6F0+i*64);
     func_0011C168(&tmp.matrices.skinProduct,&tmp.skin.inverse,matrix);
     tmp.matrices.skin=tmp.matrices.skinProduct;
     Unpack(&D_002DEA28,&tmp.matrices.skin,16,0x6C04C000|base);
     base+=4;
    }
    if(skin->second){M4*matrix=(M4*)(skin->owner+0x7F0+i*64);Unpack(&D_002DEA28,matrix,16,0x6C04C000|base);base+=4;}
   }
  }
  Align(&D_002DEA28);
  *(uint*)tag|=(((int)((uint)D_002DEA28.cur-(uint)tag))>>4)-1;
  *(ulong*)D_002DEA28.cur=0x60000000UL;D_002DEA28.cur+=16;
  Q*q=func_001CD998();
  switch((unsigned char)entry->flags>>3){
  case 3:case 4:
   if(alternate)q->kind=tmp.skin.parameters.f[0]==1.0f?22:23;
   else if(tmp.skin.parameters.f[0]==1.0f)q->kind=(unsigned char)entry->flags>>3;
   else q->kind=(entry->flags&0xF8)==0x18?5:6;
   break;
  case 5:case 6:q->kind=alternate?23:((unsigned char)entry->flags>>3);break;
  case 7:case 8:q->kind=(unsigned char)entry->flags>>3;break;
  case 9:q->kind=alternate?24:((unsigned char)entry->flags>>3);break;
  case 10:q->kind=alternate?25:((unsigned char)entry->flags>>3);break;
  default:break;
  }
  if(entry->flags&0x400)q->distance=descriptor->distance;
  else *(int*)&q->distance=SquareBits(difference.q);
  q->start=start;q->data=entry->data;
 }
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_ulong[(sizeof(ulong)==8)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_WORD[(sizeof(WORD)==4)?1:-1];
typedef char layout_M4[(sizeof(M4)==0x40)?1:-1];
typedef char layout_M3[(sizeof(M3)==0x30)?1:-1];
typedef char layout_V3[(sizeof(V3)==12)?1:-1];
typedef char layout_SPHERE[(sizeof(SPHERE)==16)?1:-1];
typedef char layout_LOCAL_SPHERE[(sizeof(LOCAL_SPHERE)==24)?1:-1];
typedef char layout_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_T[(sizeof(T)==0x80)?1:-1];
typedef char layout_BONE[(sizeof(BONE)==0x50)?1:-1];
typedef char layout_SKIN[(sizeof(SKIN)==0x24)?1:-1];
typedef char layout_D[(sizeof(D)==0x14)?1:-1];
typedef char layout_E[(sizeof(E)==0x28)?1:-1];
typedef char layout_FLAGS[(sizeof(FLAGS)==8)?1:-1];
typedef char layout_NODE[(sizeof(NODE)==0x64)?1:-1];
typedef char layout_P[(sizeof(P)==0x60)?1:-1];
typedef char layout_SHADER[(sizeof(SHADER)==0x30)?1:-1];
typedef char layout_ENV[(sizeof(ENV)==0xD0)?1:-1];
typedef char layout_GAME[(sizeof(GAME)==0x3D60)?1:-1];
typedef char layout_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_R[(sizeof(R)==16)?1:-1];
typedef char layout_Q[(sizeof(Q)==16)?1:-1];
typedef char layout_MATRICES[(sizeof(MATRICES)==0x100)?1:-1];
typedef char layout_SKIN_WORK[(sizeof(SKIN_WORK)==0x50)?1:-1];
typedef char layout_TMP[(sizeof(TMP)==0x100)?1:-1];
typedef char layout_U_q[((unsigned long)&((U*)0)->q==0x0)?1:-1];
typedef char layout_U_f[((unsigned long)&((U*)0)->f==0x0)?1:-1];
typedef char layout_U_u[((unsigned long)&((U*)0)->u==0x0)?1:-1];
typedef char layout_WORD_bits[((unsigned long)&((WORD*)0)->bits==0x0)?1:-1];
typedef char layout_WORD_value[((unsigned long)&((WORD*)0)->value==0x0)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_T_matrix[((unsigned long)&((T*)0)->matrix==0x40)?1:-1];
typedef char layout_BONE_transform[((unsigned long)&((BONE*)0)->transform==0xc)?1:-1];
typedef char layout_BONE_matrix[((unsigned long)&((BONE*)0)->matrix==0x10)?1:-1];
typedef char layout_SKIN_owner[((unsigned long)&((SKIN*)0)->owner==0xc)?1:-1];
typedef char layout_SKIN_count[((unsigned long)&((SKIN*)0)->count==0x10)?1:-1];
typedef char layout_SKIN_first[((unsigned long)&((SKIN*)0)->first==0x14)?1:-1];
typedef char layout_SKIN_second[((unsigned long)&((SKIN*)0)->second==0x18)?1:-1];
typedef char layout_SKIN_base[((unsigned long)&((SKIN*)0)->base==0x20)?1:-1];
typedef char layout_D_count[((unsigned long)&((D*)0)->count==0x1)?1:-1];
typedef char layout_D_distance[((unsigned long)&((D*)0)->distance==0x4)?1:-1];
typedef char layout_D_base[((unsigned long)&((D*)0)->base==0xc)?1:-1];
typedef char layout_E_transform[((unsigned long)&((E*)0)->transform==0x4)?1:-1];
typedef char layout_E_parent[((unsigned long)&((E*)0)->parent==0x8)?1:-1];
typedef char layout_E_flags[((unsigned long)&((E*)0)->flags==0xc)?1:-1];
typedef char layout_E_data[((unsigned long)&((E*)0)->data==0x10)?1:-1];
typedef char layout_E_bones[((unsigned long)&((E*)0)->bones==0x18)?1:-1];
typedef char layout_E_skin[((unsigned long)&((E*)0)->skin==0x1c)?1:-1];
typedef char layout_SPHERE_center[((unsigned long)&((SPHERE*)0)->center==0x0)?1:-1];
typedef char layout_SPHERE_radius[((unsigned long)&((SPHERE*)0)->radius==0xc)?1:-1];
typedef char layout_LOCAL_SPHERE_sphere[((unsigned long)&((LOCAL_SPHERE*)0)->sphere==0x0)?1:-1];
typedef char layout_LOCAL_SPHERE_range[((unsigned long)&((LOCAL_SPHERE*)0)->range==0x10)?1:-1];
typedef char layout_FLAGS_bits[((unsigned long)&((FLAGS*)0)->bits==0x0)?1:-1];
typedef char layout_FLAGS_raw[((unsigned long)&((FLAGS*)0)->raw==0x0)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_range[((unsigned long)&((NODE*)0)->range==0x38)?1:-1];
typedef char layout_NODE_frame[((unsigned long)&((NODE*)0)->frame==0x60)?1:-1];
typedef char layout_P_owner[((unsigned long)&((P*)0)->owner==0x0)?1:-1];
typedef char layout_P_stamp[((unsigned long)&((P*)0)->stamp==0x4)?1:-1];
typedef char layout_P_center[((unsigned long)&((P*)0)->center==0x10)?1:-1];
typedef char layout_P_radius[((unsigned long)&((P*)0)->radius==0x20)?1:-1];
typedef char layout_P_objectCount[((unsigned long)&((P*)0)->objectCount==0x24)?1:-1];
typedef char layout_P_objects[((unsigned long)&((P*)0)->objects==0x28)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x34)?1:-1];
typedef char layout_P_count[((unsigned long)&((P*)0)->count==0x38)?1:-1];
typedef char layout_P_descriptors[((unsigned long)&((P*)0)->descriptors==0x3c)?1:-1];
typedef char layout_P_entries[((unsigned long)&((P*)0)->entries==0x40)?1:-1];
typedef char layout_P_spheres[((unsigned long)&((P*)0)->spheres==0x44)?1:-1];
typedef char layout_P_stampId[((unsigned long)&((P*)0)->stampId==0x4c)?1:-1];
typedef char layout_P_flags[((unsigned long)&((P*)0)->flags==0x50)?1:-1];
typedef char layout_SHADER_words[((unsigned long)&((SHADER*)0)->words==0x0)?1:-1];
typedef char layout_SHADER_clip[((unsigned long)&((SHADER*)0)->clip==0x24)?1:-1];
typedef char layout_SHADER_reference[((unsigned long)&((SHADER*)0)->reference==0x28)?1:-1];
typedef char layout_SHADER_size[((unsigned long)&((SHADER*)0)->size==0x2c)?1:-1];
typedef char layout_ENV_gain[((unsigned long)&((ENV*)0)->gain==0x1c)?1:-1];
typedef char layout_ENV_near[((unsigned long)&((ENV*)0)->near==0x48)?1:-1];
typedef char layout_ENV_camera[((unsigned long)&((ENV*)0)->camera==0x90)?1:-1];
typedef char layout_ENV_planes[((unsigned long)&((ENV*)0)->planes==0xa0)?1:-1];
typedef char layout_GAME_alternate[((unsigned long)&((GAME*)0)->alternate==0x3bec)?1:-1];
typedef char layout_GAME_stamp[((unsigned long)&((GAME*)0)->stamp==0x3d5c)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_R_cur[((unsigned long)&((R*)0)->cur==0xc)?1:-1];
typedef char layout_Q_kind[((unsigned long)&((Q*)0)->kind==0x0)?1:-1];
typedef char layout_Q_distance[((unsigned long)&((Q*)0)->distance==0x4)?1:-1];
typedef char layout_Q_start[((unsigned long)&((Q*)0)->start==0x8)?1:-1];
typedef char layout_Q_data[((unsigned long)&((Q*)0)->data==0xc)?1:-1];
typedef char layout_MATRICES_source[((unsigned long)&((MATRICES*)0)->source==0x0)?1:-1];
typedef char layout_MATRICES_product[((unsigned long)&((MATRICES*)0)->product==0x40)?1:-1];
typedef char layout_MATRICES_skin[((unsigned long)&((MATRICES*)0)->skin==0x80)?1:-1];
typedef char layout_MATRICES_skinProduct[((unsigned long)&((MATRICES*)0)->skinProduct==0xc0)?1:-1];
typedef char layout_SKIN_WORK_parameters[((unsigned long)&((SKIN_WORK*)0)->parameters==0x0)?1:-1];
typedef char layout_SKIN_WORK_inverse[((unsigned long)&((SKIN_WORK*)0)->inverse==0x10)?1:-1];
