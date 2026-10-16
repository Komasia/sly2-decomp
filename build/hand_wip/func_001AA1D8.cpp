typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M4{U row[4];};
struct LO{char pad[0x40];M4 matrix;};
struct FILTER;struct CONTACT;struct WORLD;
struct SHAPE{LO*owner;FILTER*filters;float radius;int unknownC;unsigned long flags;int filterMask;int first;M4 matrix;SHAPE*next;char pad64[8];int capacity;char pad70[4];void*geometry;int count;U*vertices;char pad80[0x28];int oldGeneration,generation;};
struct BODY{char pad0[0x20];U position;float radius;SHAPE*shapes;char pad38[0x6C-0x38];CONTACT*contacts;unsigned long flags;};
struct ENTRY{char prefix[8];void*polygon;};
struct REQ{int bytes,alignment;};struct FRAME{};
struct WORK{int limit;ENTRY*end;CONTACT*head,*temporary;int capacity;ENTRY*buffer;int hasLargeFilter;ENTRY*begin;int length,status;CONTACT**temporaryAddress;FRAME*frameAddress;};
extern "C"{
 FRAME*func_001AE478(FRAME*);void func_001AE4A0(FRAME*,int);void*func_001AE318(REQ*);
 int func_00118A88(void*,int,qword,float,int*,ENTRY**);
 FILTER*func_001F7530(FILTER*,int);
 void func_001A9D38(WORLD*,SHAPE*,SHAPE*,CONTACT**);
 void func_001A9C40(WORLD*,SHAPE*,SHAPE*,CONTACT**);
 void func_001A9B28(WORLD*,SHAPE*,SHAPE*,int,ENTRY*,CONTACT**);
 void func_001A8B50(WORLD*,SHAPE*,SHAPE*,int,ENTRY*,ENTRY*,CONTACT**);
 void func_001A9FE0(WORLD*,CONTACT*,CONTACT**);CONTACT*func_001AA020(WORLD*,CONTACT*);
 void func_001AA0B0(WORLD*,BODY*,BODY*,SHAPE*,int,void*,void*,CONTACT**);
 extern ENTRY D_002BBB20;
}
static inline float Abs(float x){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(x));return r;}
static inline int Max(int a,int b){return a<b?b:a;}
static inline int Min(int a,int b){return a<b?a:b;}
static inline float DistanceSquared(U*a,U*b){
 qword difference,one;float result;__asm__("vsub.xyzw %0,%1,%2":"=j"(difference):"j"(a->q),"j"(b->q));
 __asm__("vmul.xyz %0,%0,%0":"+j"(difference));
 __asm__("vaddw.x %0,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%0,%1z":"=&j"(one),"+j"(difference));
 __asm__("qmfc2.ni %0,%1":"=r"(result):"j"(difference));return result;
}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M4_Size[sizeof(M4)==64?1:-1];
typedef char SHAPE_Size[sizeof(SHAPE)==176?1:-1];
typedef char BODY_Size[sizeof(BODY)==128?1:-1];
typedef char ENTRY_Size[sizeof(ENTRY)==12?1:-1];
typedef char REQ_Size[sizeof(REQ)==8?1:-1];
typedef char FRAME_Size[sizeof(FRAME)==1?1:-1];
typedef char WORK_Size[sizeof(WORK)==48?1:-1];
typedef char SHAPE_owner_Offset[FIELD_OFFSET(SHAPE,owner)==0?1:-1];
typedef char SHAPE_filters_Offset[FIELD_OFFSET(SHAPE,filters)==4?1:-1];
typedef char SHAPE_radius_Offset[FIELD_OFFSET(SHAPE,radius)==8?1:-1];
typedef char SHAPE_flags_Offset[FIELD_OFFSET(SHAPE,flags)==16?1:-1];
typedef char SHAPE_filterMask_Offset[FIELD_OFFSET(SHAPE,filterMask)==24?1:-1];
typedef char SHAPE_first_Offset[FIELD_OFFSET(SHAPE,first)==28?1:-1];
typedef char SHAPE_matrix_Offset[FIELD_OFFSET(SHAPE,matrix)==32?1:-1];
typedef char SHAPE_next_Offset[FIELD_OFFSET(SHAPE,next)==96?1:-1];
typedef char SHAPE_capacity_Offset[FIELD_OFFSET(SHAPE,capacity)==108?1:-1];
typedef char SHAPE_geometry_Offset[FIELD_OFFSET(SHAPE,geometry)==116?1:-1];
typedef char SHAPE_count_Offset[FIELD_OFFSET(SHAPE,count)==120?1:-1];
typedef char SHAPE_vertices_Offset[FIELD_OFFSET(SHAPE,vertices)==124?1:-1];
typedef char SHAPE_oldGeneration_Offset[FIELD_OFFSET(SHAPE,oldGeneration)==168?1:-1];
typedef char SHAPE_generation_Offset[FIELD_OFFSET(SHAPE,generation)==172?1:-1];
typedef char BODY_position_Offset[FIELD_OFFSET(BODY,position)==32?1:-1];
typedef char BODY_radius_Offset[FIELD_OFFSET(BODY,radius)==48?1:-1];
typedef char BODY_shapes_Offset[FIELD_OFFSET(BODY,shapes)==52?1:-1];
typedef char BODY_contacts_Offset[FIELD_OFFSET(BODY,contacts)==108?1:-1];
typedef char BODY_flags_Offset[FIELD_OFFSET(BODY,flags)==112?1:-1];
typedef char LO_matrix_Offset[FIELD_OFFSET(LO,matrix)==64?1:-1];
typedef char ENTRY_polygon_Offset[FIELD_OFFSET(ENTRY,polygon)==8?1:-1];
typedef char REQ_bytes_Offset[FIELD_OFFSET(REQ,bytes)==0?1:-1];
typedef char REQ_alignment_Offset[FIELD_OFFSET(REQ,alignment)==4?1:-1];
typedef char WORK_limit_Offset[FIELD_OFFSET(WORK,limit)==0?1:-1];
typedef char WORK_end_Offset[FIELD_OFFSET(WORK,end)==4?1:-1];
typedef char WORK_head_Offset[FIELD_OFFSET(WORK,head)==8?1:-1];
typedef char WORK_temporary_Offset[FIELD_OFFSET(WORK,temporary)==12?1:-1];
typedef char WORK_capacity_Offset[FIELD_OFFSET(WORK,capacity)==16?1:-1];
typedef char WORK_buffer_Offset[FIELD_OFFSET(WORK,buffer)==20?1:-1];
typedef char WORK_hasLargeFilter_Offset[FIELD_OFFSET(WORK,hasLargeFilter)==24?1:-1];
typedef char WORK_begin_Offset[FIELD_OFFSET(WORK,begin)==28?1:-1];
typedef char WORK_length_Offset[FIELD_OFFSET(WORK,length)==32?1:-1];
typedef char WORK_status_Offset[FIELD_OFFSET(WORK,status)==36?1:-1];
typedef char WORK_temporaryAddress_Offset[FIELD_OFFSET(WORK,temporaryAddress)==40?1:-1];
typedef char WORK_frameAddress_Offset[FIELD_OFFSET(WORK,frameAddress)==44?1:-1];
extern "C" CONTACT*func_001AA1D8(WORLD*world,BODY*small,BODY*large){
 FRAME frame;REQ request;WORK w;BODY*temp=small;
 w.head=0;
 if(small->radius>large->radius){small=large;large=temp;}
 w.capacity=0;w.frameAddress=&frame;REQ*r=&request;SHAPE*a;
 for(a=large->shapes;a;a=a->next)w.capacity=Max(w.capacity,a->capacity);
 (void)func_001AE478(w.frameAddress);
 w.capacity=Min(w.capacity,0x1555);
 r->bytes=w.capacity*sizeof(ENTRY);r->alignment=16;
 w.buffer=(ENTRY*)func_001AE318(r);
 for(a=large->shapes;a;a=a->next){
  w.hasLargeFilter=a->filterMask!=0;
  if((a->flags&(1UL<<48))&&!w.hasLargeFilter)continue;
  w.status=2;
  if((a->flags&(1UL<<49))||(small->flags&0x20)){
   w.end=0;w.begin=0;w.length=0;
  }else{
   w.limit=w.capacity;w.end=w.buffer;w.begin=w.buffer;
   w.status=func_00118A88(a->geometry,0x7FFFFFFF,small->position.q,small->radius,&w.limit,&w.end);
   if(w.status==1)continue;
   if(w.status==0){w.end=&D_002BBB20;w.begin=&D_002BBB20;w.length=0;}
   else{w.length=w.end-w.begin;w.end--;}
  }
  w.temporaryAddress=&w.temporary;
  for(SHAPE*b=small->shapes;b;b=b->next){
   int hasSmallFilter=b->filterMask!=0;unsigned long bFilterFlag=b->flags&(1UL<<48);
   if(bFilterFlag&&!hasSmallFilter)continue;
   if((a->flags&(1UL<<48))&&bFilterFlag)continue;
   CONTACT**all=&w.head;CONTACT**destination=all;w.temporary=0;
   if(w.hasLargeFilter){
    int match=func_001F7530(b->filters,a->filterMask)!=0;
    if(a->flags&(1UL<<48)){if(!match)continue;destination=w.temporaryAddress;}
    else if(match){destination=(b->flags&(1UL<<48))?all:w.temporaryAddress;}
   }
   if(hasSmallFilter){
    int match=func_001F7530(a->filters,b->filterMask)!=0;
    if(b->flags&(1UL<<48)){if(!match)continue;destination=w.temporaryAddress;}
    else if(match&&!(a->flags&(1UL<<48)))destination=w.temporaryAddress;
   }
   CONTACT*previous=*destination;
   if(b->generation!=b->oldGeneration||a->generation!=a->oldGeneration){
    if(b->first<b->count)func_001A9D38(world,b,a,destination);
    if(a->first<a->count)func_001A9D38(world,a,b,destination);
   }
   if(*destination==previous){
    if(a->flags&(1UL<<49)){
     if(b->flags&(1UL<<49))func_001A9C40(world,b,a,destination);
     else func_001A9B28(world,a,b,0,0,destination);
    }else if(b->flags&(1UL<<49)){
     int suppress=0;
     if(w.status){if(1.0f<DistanceSquared(&a->owner->matrix.row[3],&small->position)||1.0f<Abs(a->radius-small->radius))suppress=1;}
     func_001A9B28(world,b,a,suppress?0:w.length,suppress?0:w.begin,destination);
    }else func_001A8B50(world,b,a,w.length,w.begin,w.end,destination);
   }
   if(w.temporary){
    int copied=0;
    if(w.hasLargeFilter){
     if(a->flags&(1UL<<48))func_001A9FE0(world,w.temporary,&large->contacts);
     else if(!(b->flags&(1UL<<48))){copied=1;func_001A9FE0(world,func_001AA020(world,w.temporary),&large->contacts);}
    }
    if(hasSmallFilter){
     if(b->flags&(1UL<<48))func_001A9FE0(world,w.temporary,&small->contacts);
     else if(!(a->flags&(1UL<<48))){copied=1;func_001A9FE0(world,func_001AA020(world,w.temporary),&small->contacts);}
    }
    if(copied)func_001A9FE0(world,w.temporary,all);
   }
  }
  if(!(a->flags&(1UL<<48)))func_001AA0B0(world,small,large,a,a->capacity,a->geometry,a->geometry,&w.head);
 }
 for(SHAPE*b=small->shapes;b;b=b->next){if(!(b->flags&(1UL<<48)))func_001AA0B0(world,large,small,b,b->capacity,b->geometry,b->geometry,&w.head);}
 CONTACT*result=w.head;func_001AE4A0(w.frameAddress,2);return result;
}
