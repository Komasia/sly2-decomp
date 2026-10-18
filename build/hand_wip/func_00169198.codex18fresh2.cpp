typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef union U{qword q;float f[4];uint u[4];}U;
typedef struct M4{U r[4];}M4;
typedef struct V3{float x,y,z;}V3;
typedef struct SPHERE{V3 center;float radius;}SPHERE;
typedef struct LOCAL_SPHERE{SPHERE sphere;char pad10[8];}LOCAL_SPHERE;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct T{char pad0[0x40];M4 matrix;}T;
typedef struct BONE{int value;float unknown;short index,padA;T*transform;M4 matrix;}BONE;
typedef struct SKIN{char pad0[0xC];char*owner;int count,first,second;int pad1C;uint base;}SKIN;
typedef struct D{signed char kind,count;short channel;float distance;void*chain;uint base;uint words;}D;
typedef struct E{int unknown;T*transform;M4*parent;uint flags;char*data;uint word;BONE*bones;SKIN*skin;int pad20;SPHERE*sphere;}E;
typedef struct P{char pad0[0x24];int objectCount;void**objects;char pad2C[8];uint mode;int count;D*descriptors;E*entries;LOCAL_SPHERE*spheres;char pad48[8];float scale;}P;
typedef struct NODE{char pad0[0xC];VTE*vt;char pad10[0xF4];int count;void*sources[0];}NODE;
struct R {
 char pad0[0xC];unsigned char*cur;
 void Word(uint);
 void Copy(const void*,int);
 void Unpack(const void*,int,uint);
 unsigned char*Begin();
 void End(unsigned char*);
};
typedef struct Q{int kind;float distance;unsigned char*start;char*data;}Q;
typedef struct SHADER{uint words[12];}SHADER;
typedef struct MATRICES{M4 source,product,boneProduct,skinProduct;}MATRICES;
typedef struct BONESCRATCH{U parameters;M4 bone,skin;}BONESCRATCH;
typedef union TMP{MATRICES matrices;BONESCRATCH bones;}TMP;
typedef struct WORK{SHADER shader;M4 model;TMP tmp;NODE*context;SHADER*shaderRef;int kind;U difference,sphere;unsigned char*start;int next;}WORK;
extern "C" {
extern R D_002DEA28;extern char D_003DD490[];extern M4 D_002A2D30;
extern void*func_002333B4(void*,int,uint);
extern void func_001A4AD8(void*,int,void**,SHADER*);
extern int func_001EDA20(void*),func_001BEE10(NODE*,int);
extern void func_001AE5A0(void*,const void*,uint);
extern void*func_0023320C(void*,const void*,uint);
extern M4*func_0011C168(M4*,const M4*,const M4*);
extern M4*func_0011C318(M4*,const M4*);
extern qword func_001A62E8(void*);
extern Q*func_001CD998(void);
}
static inline void CopyMatrix(M4&out,const M4&input){(void)func_0023320C(&out,&input,64);}
inline void*operator new(unsigned,void*place){return place;}
extern M4 Product(const M4&,const M4&) __asm__("func_0011C168");
extern M4 Inverse(const M4&) __asm__("func_0011C318");
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Transform(M4*m,qword source){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(source));return r;}
static inline int SquareBits(qword a){qword d,one;int bits;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));return bits;}
static inline void Update(void*object){VTE*e=&((NODE*)object)->vt[8];((void(*)(void*))e->fn)((char*)object+e->delta);}
struct WORD4 {
 uint a,b,c,d;
 WORD4(const uint*source):a(source[0]),b(source[1]),c(source[2]),d(source[3]){}
};
inline void R::Word(uint value) {*(uint*)cur=value;cur+=4;}
inline void R::Copy(const void*input,int words) {
 const uint*source=(const uint*)input;
 uint*destination=(uint*)cur;
 int remaining=words-4;
 do {
  uint a=source[0],b=source[1],c=source[2],d=source[3];
  source+=4;
  destination[0]=a;destination[1]=b;destination[2]=c;destination[3]=d;
  destination+=4;
  remaining-=4;
 }while(remaining>=0);
 cur+=words*4;
}
inline void R::Unpack(const void*source,int words,uint address) {
 Word(0x6C00C000U|((words/4)<<16)|address);
 Copy(source,words);
}
inline unsigned char*R::Begin() {
 unsigned char*tag=cur;*(ulong*)tag=0x10000000UL;cur+=16;
 return tag;
}
inline void R::End(unsigned char*tag) {
 while((uint)cur&15){*(uint*)cur=0;cur+=4;}
 *(uint*)tag|=(((int)((uint)cur-(uint)tag))>>4)-1;
 *(ulong*)cur=0x60000000UL;cur+=16;
}
extern "C" void func_00169198(P*p,NODE*context) {
 SHADER shader;
 M4 model;
 SHADER*shaderRef;
 int kind;
 U difference,sphere;
 unsigned char*start;
 int next;
 if(context->count){
  func_002333B4(&shader,0,sizeof(SHADER));
  shaderRef=&shader;
  func_001A4AD8(D_003DD490,context->count,context->sources,&shader);
 }else shaderRef=0;
 int index=0;
 for(;index<p->objectCount;++index){
  void*object=p->objects[index];
  if(func_001EDA20(object))Update(object);
 }
 for(index=0;index<p->count;index=next){
  E*entry=&p->entries[index];
  D*descriptor=&p->descriptors[index];
  next=index+1;
  uint flags=entry->flags;
  if(flags&0x800)continue;
  if((flags&7)==2)continue;
  kind=func_001BEE10(context,(flags>>3)&31);
  if(kind==-1)continue;
  if(entry->flags&0x1000){
   func_001AE5A0(&model,entry->data+0x14,sizeof(M4));
  }else{
   M4*parent=entry->parent;
   M4 source;
   CopyMatrix(source,entry->transform->matrix);
   if(parent)CopyMatrix(source,Product(source,*parent));
   model=source;
  }
  if(entry->sphere){
   sphere.q=*(const qword*)entry->sphere;
   difference.q=Sub(sphere.q,func_001A62E8(context));
  }else{
   U center;
   func_001AE5A0(&center,&p->spheres[index].sphere.center,sizeof(V3));
   difference.q=Transform(&model,center.q);
  }
  start=D_002DEA28.cur;
  if(entry->flags&0x100){
   ulong low=(ulong)(int)(shaderRef->words[5]|0x40000000U);
   ulong high=(ulong)(int)shaderRef->words[6]<<32;
   *(ulong*)D_002DEA28.cur=low|high;
   D_002DEA28.cur+=16;
  }
  unsigned char*tag=D_002DEA28.Begin();
  if(entry->bones){
   D_002DEA28.Word(0x6C04C000U);
   next=++index;
   D_002DEA28.Copy(&D_002A2D30,16);
  }else{
   D_002DEA28.Word(0x6C04C000U);
   next=++index;
   D_002DEA28.Copy(&model,16);
  }
  U parameters;
  parameters.f[0]=1.0f;
  parameters.f[1]=1.0f;
  parameters.f[2]=p->scale;
  parameters.u[3]=(entry->flags&0x200)?p->mode:0;
  D_002DEA28.Unpack(&parameters,4,8);
  if(entry->bones){
   for(int boneIndex=0;boneIndex<descriptor->count;++boneIndex){
    BONE*bone=&entry->bones[boneIndex];
    M4 boneMatrix;
    if(bone->transform)boneMatrix=Product(bone->transform->matrix,bone->matrix);
    else boneMatrix=bone->matrix;
    D_002DEA28.Unpack(&boneMatrix,16,descriptor->base+boneIndex*4);
   }
  }
  if(entry->skin){
   SKIN*skin=entry->skin;
   uint address=skin->base;
   M4 inverse=Inverse(model);
   for(index=0;index<skin->count;++index){
    if(skin->first){
     const M4*matrix=(const M4*)(skin->owner+0x6F0+index*64);
     M4 skinMatrix=Product(inverse,*matrix);
     D_002DEA28.Unpack(&skinMatrix,16,address);
     address+=4;
    }
    if(skin->second){
     const M4*matrix=(const M4*)(skin->owner+0x7F0+index*64);
     D_002DEA28.Unpack(matrix,16,address);
     address+=4;
    }
   }
  }
  D_002DEA28.End(tag);
  Q*queue=func_001CD998();
  queue->kind=kind;
  if(entry->flags&0x400)queue->distance=descriptor->distance;
  else *(int*)&queue->distance=SquareBits(difference.q);
  queue->start=start;
  queue->data=entry->data;
 }
}
typedef char layout_size_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_size_voidpointer[(sizeof(void*)==4)?1:-1];
typedef char layout_size_ulong[(sizeof(ulong)==8)?1:-1];
typedef char layout_size_U[(sizeof(U)==16)?1:-1];
typedef char layout_size_M4[(sizeof(M4)==64)?1:-1];
typedef char layout_size_V3[(sizeof(V3)==12)?1:-1];
typedef char layout_size_SPHERE[(sizeof(SPHERE)==16)?1:-1];
typedef char layout_size_LOCAL_SPHERE[(sizeof(LOCAL_SPHERE)==24)?1:-1];
typedef char layout_size_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_size_T[(sizeof(T)==0x80)?1:-1];
typedef char layout_size_BONE[(sizeof(BONE)==0x50)?1:-1];
typedef char layout_size_SKIN[(sizeof(SKIN)==0x24)?1:-1];
typedef char layout_size_D[(sizeof(D)==0x14)?1:-1];
typedef char layout_size_E[(sizeof(E)==0x28)?1:-1];
typedef char layout_size_P[(sizeof(P)==0x54)?1:-1];
typedef char layout_size_NODE[(sizeof(NODE)==0x108)?1:-1];
typedef char layout_size_R[(sizeof(R)==16)?1:-1];
typedef char layout_size_Q[(sizeof(Q)==16)?1:-1];
typedef char layout_size_SHADER[(sizeof(SHADER)==0x30)?1:-1];
typedef char layout_size_MATRICES[(sizeof(MATRICES)==0x100)?1:-1];
typedef char layout_size_BONESCRATCH[(sizeof(BONESCRATCH)==0x90)?1:-1];
typedef char layout_size_TMP[(sizeof(TMP)==0x100)?1:-1];
typedef char layout_size_WORK[(sizeof(WORK)==0x1B0)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_T_matrix[((unsigned long)&((T*)0)->matrix==0x40)?1:-1];
typedef char layout_BONE_value[((unsigned long)&((BONE*)0)->value==0x0)?1:-1];
typedef char layout_BONE_index[((unsigned long)&((BONE*)0)->index==0x8)?1:-1];
typedef char layout_BONE_transform[((unsigned long)&((BONE*)0)->transform==0xc)?1:-1];
typedef char layout_BONE_matrix[((unsigned long)&((BONE*)0)->matrix==0x10)?1:-1];
typedef char layout_SKIN_owner[((unsigned long)&((SKIN*)0)->owner==0xc)?1:-1];
typedef char layout_SKIN_count[((unsigned long)&((SKIN*)0)->count==0x10)?1:-1];
typedef char layout_SKIN_first[((unsigned long)&((SKIN*)0)->first==0x14)?1:-1];
typedef char layout_SKIN_second[((unsigned long)&((SKIN*)0)->second==0x18)?1:-1];
typedef char layout_SKIN_base[((unsigned long)&((SKIN*)0)->base==0x20)?1:-1];
typedef char layout_D_count[((unsigned long)&((D*)0)->count==0x1)?1:-1];
typedef char layout_D_distance[((unsigned long)&((D*)0)->distance==0x4)?1:-1];
typedef char layout_D_chain[((unsigned long)&((D*)0)->chain==0x8)?1:-1];
typedef char layout_D_base[((unsigned long)&((D*)0)->base==0xc)?1:-1];
typedef char layout_E_transform[((unsigned long)&((E*)0)->transform==0x4)?1:-1];
typedef char layout_E_parent[((unsigned long)&((E*)0)->parent==0x8)?1:-1];
typedef char layout_E_flags[((unsigned long)&((E*)0)->flags==0xc)?1:-1];
typedef char layout_E_data[((unsigned long)&((E*)0)->data==0x10)?1:-1];
typedef char layout_E_bones[((unsigned long)&((E*)0)->bones==0x18)?1:-1];
typedef char layout_E_skin[((unsigned long)&((E*)0)->skin==0x1c)?1:-1];
typedef char layout_E_sphere[((unsigned long)&((E*)0)->sphere==0x24)?1:-1];
typedef char layout_P_objectCount[((unsigned long)&((P*)0)->objectCount==0x24)?1:-1];
typedef char layout_P_objects[((unsigned long)&((P*)0)->objects==0x28)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x34)?1:-1];
typedef char layout_P_count[((unsigned long)&((P*)0)->count==0x38)?1:-1];
typedef char layout_P_descriptors[((unsigned long)&((P*)0)->descriptors==0x3c)?1:-1];
typedef char layout_P_entries[((unsigned long)&((P*)0)->entries==0x40)?1:-1];
typedef char layout_P_spheres[((unsigned long)&((P*)0)->spheres==0x44)?1:-1];
typedef char layout_P_scale[((unsigned long)&((P*)0)->scale==0x50)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_count[((unsigned long)&((NODE*)0)->count==0x104)?1:-1];
typedef char layout_NODE_sources[((unsigned long)&((NODE*)0)->sources==0x108)?1:-1];
typedef char layout_R_cur[((unsigned long)&((R*)0)->cur==0xc)?1:-1];
typedef char layout_Q_kind[((unsigned long)&((Q*)0)->kind==0x0)?1:-1];
typedef char layout_Q_distance[((unsigned long)&((Q*)0)->distance==0x4)?1:-1];
typedef char layout_Q_start[((unsigned long)&((Q*)0)->start==0x8)?1:-1];
typedef char layout_Q_data[((unsigned long)&((Q*)0)->data==0xc)?1:-1];
typedef char layout_MATRICES_source[((unsigned long)&((MATRICES*)0)->source==0x0)?1:-1];
typedef char layout_MATRICES_product[((unsigned long)&((MATRICES*)0)->product==0x40)?1:-1];
typedef char layout_MATRICES_boneProduct[((unsigned long)&((MATRICES*)0)->boneProduct==0x80)?1:-1];
typedef char layout_MATRICES_skinProduct[((unsigned long)&((MATRICES*)0)->skinProduct==0xc0)?1:-1];
typedef char layout_BONESCRATCH_parameters[((unsigned long)&((BONESCRATCH*)0)->parameters==0x0)?1:-1];
typedef char layout_BONESCRATCH_bone[((unsigned long)&((BONESCRATCH*)0)->bone==0x10)?1:-1];
typedef char layout_BONESCRATCH_skin[((unsigned long)&((BONESCRATCH*)0)->skin==0x50)?1:-1];
typedef char layout_WORK_shader[((unsigned long)&((WORK*)0)->shader==0x0)?1:-1];
typedef char layout_WORK_model[((unsigned long)&((WORK*)0)->model==0x30)?1:-1];
typedef char layout_WORK_tmp[((unsigned long)&((WORK*)0)->tmp==0x70)?1:-1];
typedef char layout_WORK_context[((unsigned long)&((WORK*)0)->context==0x170)?1:-1];
typedef char layout_WORK_shaderRef[((unsigned long)&((WORK*)0)->shaderRef==0x174)?1:-1];
typedef char layout_WORK_kind[((unsigned long)&((WORK*)0)->kind==0x178)?1:-1];
typedef char layout_WORK_difference[((unsigned long)&((WORK*)0)->difference==0x180)?1:-1];
typedef char layout_WORK_sphere[((unsigned long)&((WORK*)0)->sphere==0x190)?1:-1];
typedef char layout_WORK_start[((unsigned long)&((WORK*)0)->start==0x1a0)?1:-1];
typedef char layout_WORK_next[((unsigned long)&((WORK*)0)->next==0x1a4)?1:-1];

typedef char word_packet_bytes[(sizeof(WORD4)==16)?1:-1];
typedef char word_packet_align[(__alignof__(WORD4)==4)?1:-1];
