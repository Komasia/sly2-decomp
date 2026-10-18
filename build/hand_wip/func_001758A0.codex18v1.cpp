
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M4{U row[4];};
struct VTE{short delta,pad;void*fn;};
struct FLAGS{unsigned long value;};
struct NAME{unsigned identity;};
struct SCALE{char pad[0x20];float value;};
struct LM{float low,high;};
struct ENTRY{char pad0[0x50];LM distance,height;char pad60[8];float angle,minHit;int lineOfSight,filter,response;char pad7C[0x2C];int enabled;};
struct P{char pad0[0xC];VTE*vt;char pad10[0x18];FLAGS flags;char pad30[0xC];NAME*name;char pad40[0xE9C];ENTRY*entries[8];int count;ENTRY*current;float cooldown;char padF08[0xB4];int mode;char padFC0[4];SCALE*scale;};
struct LSG{U point;char rest[0x50];};
struct LOS{U start,end;LSG hit;};
struct HEAP{};
struct REF_DATA{int kind,value;};
struct PROPERTY{REF_DATA allowed;M4 frame;};
union SLOT{LOS line;PROPERTY property;};
struct WORK{HEAP heap;SLOT slot;int count;void**objects;void*argument;U from,to;};
struct POLY{float a,b,c;};
struct CLOCK{float time,dt;};
extern "C"{
extern CLOCK D_002DDED0;extern POLY D_002BE600;extern LM D_002BBB60;extern char D_003DD490;
int func_00132B10(P*,int);int func_0020A818(void*,P*);
qword func_001A62E8(P*);unsigned func_001C9950(unsigned);
int func_0011D910(LM*,float);qword func_001A6F00(P*,P*,qword);float func_002458F0(float,float);
int func_00175820(void*,void*);
void func_0020FAA0(void*,qword,qword,int(*)(void*,void*),void*,int*,void***);
void*func_0014CC58(int,qword,qword,int,void**,LSG*);
void*func_001AE478(void*);void func_001AE4A0(void*,int);
void func_00129EC8(void*);
void func_0020AB68(P*,ENTRY*,void*,qword);void func_0020A9A8(void*,int);
}
static inline void Store(qword*p,qword v){__asm__("sq %1,%0":"=m"(*p):"r"(v));}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Y(qword a){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(a));return f;}
static inline float Length(qword a){
 qword r,one;float f;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(r));
 __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;
}
static inline bool Blocked(LOS*line,float limit){return Length(Sub(line->start.q,line->hit.point.q))<limit;}
extern "C" int func_001758A0(P*p,P*target,void*gate){
 WORK w;
 if(p->current)return 0;
 if(!target)return 0;
 {register int enabled __asm__("$2")=(int)(target->flags.value>>60)&1;if(!enabled)return 0;}
 if(D_002DDED0.time<p->cooldown)return 0;
 if(func_00132B10(target,0x32)){
  VTE*e=&target->vt[77];
  if(((int(*)(void*))e->fn)((char*)target+e->delta))return 0;
 }
 if(gate&&!func_0020A818(gate,p))return 0;
 Store(&w.from.q,func_001A62E8(p));Store(&w.to.q,func_001A62E8(target));

 register qword delta __asm__("vf1"),square __asm__("vf2");
 register unsigned targetIdentity __asm__("$4");
 {NAME*name=target->name;
  __asm__("lqc2 $vf2,%3\n\tlqc2 $vf3,%4\n\tvsub.xyzw %0,$vf2,$vf3\n\tlw %1,%2":"=j"(delta),"=r"(targetIdentity):"m"(name->identity),"m"(w.to.q),"m"(w.from.q):"vf2","vf3");}
 register qword packed __asm__("$2");
 __asm__("vmul.xy %0,%2,%2\n\tvaddy.x %0,%0,%0y\n\tqmfc2.ni %1,%2":"=j"(square),"=r"(packed):"j"(delta));
 register float height __asm__("$f21"),distance __asm__("$f20");
 __asm__("vsqrt Q,%3x\n\tvwaitq\n\tvaddq.x %3,$vf0,Q\n\tpextuw %2,$zero,%2\n\tqmfc2.ni $v1,%3\n\tmtc1 %2,%0\n\tmtc1 $v1,%1":"=f"(height),"=f"(distance),"+r"(packed),"+j"(square): :"$3");

 if(func_001C9950(targetIdentity)==func_001C9950(p->name->identity)){
  distance+=((unsigned)target<(unsigned)p)?75.0f:-75.0f;
 }
 if((p->mode==8||p->mode==13)&&p->scale){__asm__("div.s %0,%0,%2\n\tdiv.s %1,%1,%2":"+f"(height),"+f"(distance):"f"(p->scale->value));}
 int i;
 for(i=0;i<p->count;i++){
  register ENTRY*entry __asm__("$17")=p->entries[i];
  if(!entry->enabled)continue;
  if(!func_0011D910(&entry->distance,distance))continue;
  if(!func_0011D910(&entry->height,height))continue;
  qword local=func_001A6F00(0,p,w.to.q);
  register float angle __asm__("$f5")=__builtin_fabsf(func_002458F0(Y(local),X(local)));
  register float c __asm__("$f1")=D_002BE600.c,b __asm__("$f0")=D_002BE600.b,a __asm__("$f2")=D_002BE600.a;
  b+=distance*c;b=distance*b;
  register float gain __asm__("$f1")=a+b;
  register float low __asm__("$f3")=D_002BBB60.low,high __asm__("$f4")=D_002BBB60.high;
  if(gain<low)gain=low;else if(high<gain)gain=high;
  if(entry->angle<gain*angle)continue;
  if(entry->lineOfSight){
   func_001AE478(&w.heap);
   register qword end __asm__("$6"),start __asm__("$5");
   __asm__("lq %0,%1":"=r"(end):"m"(w.to.q));
   register unsigned gameHigh __asm__("$2")=0x003E0000;register void*game __asm__("$4");
   __asm__("addiu %0,%1,-0x2B70":"=r"(game):"r"(gameHigh));
   start=w.from.q;
   register qword snapshot __asm__("$2");
   __asm__("por %0,$zero,%1":"=r"(snapshot):"r"(end));
   w.slot.line.start.q=start;w.slot.line.end.q=snapshot;
   func_0020FAA0(game,start,end,func_00175820,entry,&w.count,&w.objects);
   if(func_0014CC58(0,w.slot.line.start.q,w.slot.line.end.q,w.count,w.objects,&w.slot.line.hit)&&Blocked(&w.slot.line,entry->minHit)){func_001AE4A0(&w.heap,2);continue;}
   func_001AE4A0(&w.heap,2);
  }
  REF_DATA*allowed=&w.slot.property.allowed;allowed->kind=23;allowed->value=1;
  w.argument=(char*)entry+0x18;
  VTE*e=&p->vt[3];
  ((void(*)(void*,int,int,int,void**,REF_DATA*))e->fn)((char*)p+e->delta,0x18,0,1,&w.argument,allowed);
  if(w.slot.property.allowed.kind!=23||!w.slot.property.allowed.value){func_00129EC8(allowed);continue;}
  if(entry->response){
   e=&target->vt[32];
   void*owner=((void*(*)(void*,M4*))e->fn)((char*)target+e->delta,&w.slot.property.frame);
   func_0020AB68(p,entry,owner,w.slot.property.frame.row[3].q);
  }
  if(gate)func_0020A9A8(gate,3);
  func_00129EC8(&w.slot.property.allowed);
  return 0;
 }
 return 0;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char UnsignedLong_Size[(sizeof(unsigned long)==8)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char FLAGS_Size[(sizeof(FLAGS)==8)?1:-1];
typedef char NAME_Size[(sizeof(NAME)==4)?1:-1];
typedef char LM_Size[(sizeof(LM)==8)?1:-1];
typedef char ENTRY_Size[(sizeof(ENTRY)==0xAC)?1:-1];
typedef char LSG_Size[(sizeof(LSG)==0x60)?1:-1];
typedef char LOS_Size[(sizeof(LOS)==0x80)?1:-1];
typedef char REF_DATA_Size[(sizeof(REF_DATA)==8)?1:-1];
typedef char PROPERTY_Size[(sizeof(PROPERTY)==0x50)?1:-1];
typedef char SLOT_Size[(sizeof(SLOT)==0x80)?1:-1];
typedef char HEAP_Size[(sizeof(HEAP)==1)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0xC0)?1:-1];
typedef char POLY_Size[(sizeof(POLY)==12)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char NAME_identity_Offset[((unsigned)&((NAME*)0)->identity==0)?1:-1];
typedef char SCALE_value_Offset[((unsigned)&((SCALE*)0)->value==32)?1:-1];
typedef char LM_low_Offset[((unsigned)&((LM*)0)->low==0)?1:-1];
typedef char LM_high_Offset[((unsigned)&((LM*)0)->high==4)?1:-1];
typedef char ENTRY_distance_Offset[((unsigned)&((ENTRY*)0)->distance==80)?1:-1];
typedef char ENTRY_height_Offset[((unsigned)&((ENTRY*)0)->height==88)?1:-1];
typedef char ENTRY_angle_Offset[((unsigned)&((ENTRY*)0)->angle==104)?1:-1];
typedef char ENTRY_minHit_Offset[((unsigned)&((ENTRY*)0)->minHit==108)?1:-1];
typedef char ENTRY_lineOfSight_Offset[((unsigned)&((ENTRY*)0)->lineOfSight==112)?1:-1];
typedef char ENTRY_filter_Offset[((unsigned)&((ENTRY*)0)->filter==116)?1:-1];
typedef char ENTRY_response_Offset[((unsigned)&((ENTRY*)0)->response==120)?1:-1];
typedef char ENTRY_enabled_Offset[((unsigned)&((ENTRY*)0)->enabled==168)?1:-1];
typedef char P_vt_Offset[((unsigned)&((P*)0)->vt==12)?1:-1];
typedef char P_flags_Offset[((unsigned)&((P*)0)->flags==40)?1:-1];
typedef char P_name_Offset[((unsigned)&((P*)0)->name==60)?1:-1];
typedef char P_entries_Offset[((unsigned)&((P*)0)->entries==3804)?1:-1];
typedef char P_count_Offset[((unsigned)&((P*)0)->count==3836)?1:-1];
typedef char P_current_Offset[((unsigned)&((P*)0)->current==3840)?1:-1];
typedef char P_cooldown_Offset[((unsigned)&((P*)0)->cooldown==3844)?1:-1];
typedef char P_mode_Offset[((unsigned)&((P*)0)->mode==4028)?1:-1];
typedef char P_scale_Offset[((unsigned)&((P*)0)->scale==4036)?1:-1];
typedef char REF_DATA_kind_Offset[((unsigned)&((REF_DATA*)0)->kind==0)?1:-1];
typedef char REF_DATA_value_Offset[((unsigned)&((REF_DATA*)0)->value==4)?1:-1];
typedef char LSG_point_Offset[((unsigned)&((LSG*)0)->point==0)?1:-1];
typedef char LOS_start_Offset[((unsigned)&((LOS*)0)->start==0)?1:-1];
typedef char LOS_end_Offset[((unsigned)&((LOS*)0)->end==16)?1:-1];
typedef char LOS_hit_Offset[((unsigned)&((LOS*)0)->hit==32)?1:-1];
typedef char PROPERTY_allowed_Offset[((unsigned)&((PROPERTY*)0)->allowed==0)?1:-1];
typedef char PROPERTY_frame_Offset[((unsigned)&((PROPERTY*)0)->frame==16)?1:-1];
typedef char WORK_heap_Offset[((unsigned)&((WORK*)0)->heap==0)?1:-1];
typedef char WORK_slot_Offset[((unsigned)&((WORK*)0)->slot==16)?1:-1];
typedef char WORK_count_Offset[((unsigned)&((WORK*)0)->count==144)?1:-1];
typedef char WORK_objects_Offset[((unsigned)&((WORK*)0)->objects==148)?1:-1];
typedef char WORK_argument_Offset[((unsigned)&((WORK*)0)->argument==152)?1:-1];
typedef char WORK_from_Offset[((unsigned)&((WORK*)0)->from==160)?1:-1];
typedef char WORK_to_Offset[((unsigned)&((WORK*)0)->to==176)?1:-1];
typedef char POLY_a_Offset[((unsigned)&((POLY*)0)->a==0)?1:-1];
typedef char POLY_b_Offset[((unsigned)&((POLY*)0)->b==4)?1:-1];
typedef char POLY_c_Offset[((unsigned)&((POLY*)0)->c==8)?1:-1];

typedef char CLOCK_Size[(sizeof(CLOCK)==8)?1:-1];
typedef char CLOCK_time_Offset[((unsigned)&((CLOCK*)0)->time==0)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];

typedef char FLAGS_value_Offset[((unsigned)&((FLAGS*)0)->value==0)?1:-1];
