#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
#include "bis.h"
struct TRANSFORM;
struct SO;
struct VE{short delta,pad;TRANSFORM*(*get)(SO*,int);};
struct SO{char pad[0xC];VE*vt;};
struct V3{float f[3];};
struct D{char channel,segments;unsigned char flags;char kind;float radius;void*chain;int base,words;};
union FLAGS{uint word;struct{uint kind:3,channel:5,pad:2,volume:1,feature:1,rest:20;}bits;};
struct E{int value;TRANSFORM*transform;void*parent;FLAGS flags;void*data;uint base;void*segments;int word1C;void*object;void*sphere;};
struct SPHERE{V3 center;float radius,limit;uint metadata;};
struct P{SO*owner;char pad4[12];V3 position;float pad1C;float radius;int objectCount;SO**objects;int indexCount;int*indices;int reserved;int count;D*descriptors;E*entries;SPHERE*spheres;void*groups;};
struct PARAM{float value;int pad,kind;};
struct REQUEST{int bytes,alignment;REQUEST(int cb,int align):bytes(cb),alignment(align){}};
extern "C"{
void*func_001AE2A0(const REQUEST&);
SO*func_001ED7A8(void*,CBinaryInputStream*);
int func_0013FAD0(int,short*);
void*func_002333B4(void*,int,uint);
void func_00117EB0(CBinaryInputStream*,V3*) __asm__("ReadVector__18CBinaryInputStreamP6VECTOR");
void func_0016A000(P*,D*,E*,PARAM*,SPHERE*,int,CBinaryInputStream*);
void func_0016E438(P*,D*,E*,PARAM*,SPHERE*,int,CBinaryInputStream*);
void func_0016CAA0(P*,D*,E*,PARAM*,SPHERE*,int,CBinaryInputStream*);
void func_0016CF78(P*,D*,E*,PARAM*,SPHERE*,int,CBinaryInputStream*);
void func_00167870(P*,CBinaryInputStream*);
extern float D_002A5270;
}
static inline void*Allocate(int bytes){return func_001AE2A0(REQUEST(bytes,16));}
static inline TRANSFORM*ReadTransform(SO*owner,CBinaryInputStream*stream){VE*method=&owner->vt[51];SO*receiver=(SO*)((char*)owner+method->delta);int index=stream->S16Read();return method->get(receiver,index);}
static inline void ReadRadius(D*desc,CBinaryInputStream*stream){float radius=stream->F32Read();if(radius==D_002A5270)desc->radius=D_002A5270;else desc->radius=radius*__builtin_fabsf(radius);}
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char SO_Size[sizeof(SO)==16?1:-1];
typedef char V3_Size[sizeof(V3)==12?1:-1];
typedef char D_Size[sizeof(D)==20?1:-1];
typedef char FLAGS_Size[sizeof(FLAGS)==4?1:-1];
typedef char E_Size[sizeof(E)==40?1:-1];
typedef char SPHERE_Size[sizeof(SPHERE)==24?1:-1];
typedef char PARAM_Size[sizeof(PARAM)==12?1:-1];
typedef char REQUEST_Size[sizeof(REQUEST)==8?1:-1];
typedef char VE_delta_Offset[FIELD_OFFSET(VE,delta)==0?1:-1];
typedef char VE_get_Offset[FIELD_OFFSET(VE,get)==4?1:-1];
typedef char SO_vt_Offset[FIELD_OFFSET(SO,vt)==12?1:-1];
typedef char D_channel_Offset[FIELD_OFFSET(D,channel)==0?1:-1];
typedef char D_segments_Offset[FIELD_OFFSET(D,segments)==1?1:-1];
typedef char D_flags_Offset[FIELD_OFFSET(D,flags)==2?1:-1];
typedef char D_kind_Offset[FIELD_OFFSET(D,kind)==3?1:-1];
typedef char D_radius_Offset[FIELD_OFFSET(D,radius)==4?1:-1];
typedef char D_chain_Offset[FIELD_OFFSET(D,chain)==8?1:-1];
typedef char D_base_Offset[FIELD_OFFSET(D,base)==12?1:-1];
typedef char D_words_Offset[FIELD_OFFSET(D,words)==16?1:-1];
typedef char E_value_Offset[FIELD_OFFSET(E,value)==0?1:-1];
typedef char E_transform_Offset[FIELD_OFFSET(E,transform)==4?1:-1];
typedef char E_flags_Offset[FIELD_OFFSET(E,flags)==12?1:-1];
typedef char E_sphere_Offset[FIELD_OFFSET(E,sphere)==36?1:-1];
typedef char SPHERE_center_Offset[FIELD_OFFSET(SPHERE,center)==0?1:-1];
typedef char SPHERE_radius_Offset[FIELD_OFFSET(SPHERE,radius)==12?1:-1];
typedef char SPHERE_limit_Offset[FIELD_OFFSET(SPHERE,limit)==16?1:-1];
typedef char SPHERE_metadata_Offset[FIELD_OFFSET(SPHERE,metadata)==20?1:-1];
typedef char P_owner_Offset[FIELD_OFFSET(P,owner)==0?1:-1];
typedef char P_position_Offset[FIELD_OFFSET(P,position)==16?1:-1];
typedef char P_radius_Offset[FIELD_OFFSET(P,radius)==32?1:-1];
typedef char P_objectCount_Offset[FIELD_OFFSET(P,objectCount)==36?1:-1];
typedef char P_objects_Offset[FIELD_OFFSET(P,objects)==40?1:-1];
typedef char P_indexCount_Offset[FIELD_OFFSET(P,indexCount)==44?1:-1];
typedef char P_indices_Offset[FIELD_OFFSET(P,indices)==48?1:-1];
typedef char P_reserved_Offset[FIELD_OFFSET(P,reserved)==52?1:-1];
typedef char P_count_Offset[FIELD_OFFSET(P,count)==56?1:-1];
typedef char P_descriptors_Offset[FIELD_OFFSET(P,descriptors)==60?1:-1];
typedef char P_entries_Offset[FIELD_OFFSET(P,entries)==64?1:-1];
typedef char P_spheres_Offset[FIELD_OFFSET(P,spheres)==68?1:-1];
typedef char P_groups_Offset[FIELD_OFFSET(P,groups)==72?1:-1];
typedef char PARAM_value_Offset[FIELD_OFFSET(PARAM,value)==0?1:-1];
typedef char PARAM_kind_Offset[FIELD_OFFSET(PARAM,kind)==8?1:-1];
typedef char REQUEST_bytes_Offset[FIELD_OFFSET(REQUEST,bytes)==0?1:-1];
typedef char REQUEST_alignment_Offset[FIELD_OFFSET(REQUEST,alignment)==4?1:-1];
extern "C" void func_00167320(P*p,SO*owner,CBinaryInputStream*stream){
 int i=0;
 p->owner=owner;
 int local=stream->S8Read();
 func_00117EB0(stream,&p->position);
 p->radius=stream->F32Read();
 p->objectCount=stream->U8Read();
 p->objects=(SO**)Allocate(p->objectCount*4);
 for(;i<p->objectCount;i++)p->objects[i]=func_001ED7A8((void*)1,stream);
 i=0;
 p->indexCount=stream->U8Read();
 p->indices=(int*)Allocate(p->indexCount*4);
 p->reserved=0;
 for(;i<p->indexCount;i++)p->indices[i]=stream->S32Read();
 p->count=stream->S16Read();
 p->descriptors=(D*)Allocate(p->count*sizeof(D));
 p->entries=(E*)Allocate(p->count*sizeof(E));
 if(!local)p->spheres=(SPHERE*)Allocate(p->count*sizeof(SPHERE));
 register int entryIndex __asm__("$23")=0;if(p->count>0){PARAM param;short levels[128];float limit=D_002A5270;
 do{
  int descriptorBytes=sizeof(D),entryBytes=sizeof(E);
  descriptorBytes=entryIndex*descriptorBytes;entryBytes=entryIndex*entryBytes;
  D*desc=(D*)((char*)p->descriptors+descriptorBytes);
  E*entry=(E*)((char*)p->entries+entryBytes);
  SPHERE*sphere=p->spheres?&p->spheres[entryIndex]:0;
  func_002333B4(&param,0,sizeof(PARAM));
  int levelCount=stream->S8Read();
  if(levelCount){
   stream->Read(levelCount*2,levels);
   int bytes=stream->S32Read();
   if(!func_0013FAD0(levelCount,levels)){stream->Skip(bytes);entryIndex--;p->count--;continue;}
  }
  desc->kind=stream->S8Read();
  int copies=stream->U16Read();
  entry->transform=ReadTransform(owner,stream);
  desc->channel=stream->S8Read();
  ReadRadius(desc,stream);
  param.value=stream->F32Read();
  entry->value=stream->S32Read();
  param.kind=stream->S8Read();
  entry->flags.bits.feature=stream->S8Read();
  if(!local){
   func_00117EB0(stream,&sphere->center);
   sphere->radius=stream->F32Read();
   sphere->metadata=stream->U32Read();
   sphere->limit=stream->F32Read();
   if(sphere->limit==limit){
    switch(desc->kind){case 0:case 2:case 3:sphere->limit=1.0e10f;break;case 1:sphere->limit=2000.0f;break;}
   }
  }
  entry->flags.bits.kind=desc->kind;
  entry->flags.bits.channel=desc->channel;
  if(desc->radius!=limit)entry->flags.bits.volume=1;
  switch(desc->kind){
   case 0:func_0016A000(p,desc,entry,&param,sphere,copies,stream);break;
   case 1:func_0016E438(p,desc,entry,&param,sphere,copies,stream);break;
   case 2:func_0016CAA0(p,desc,entry,&param,sphere,copies,stream);break;
   case 3:func_0016CF78(p,desc,entry,&param,sphere,copies,stream);break;
  }
  entryIndex+=copies;
 }while(++entryIndex<p->count);
 }
 func_00167870(p,stream);
}
