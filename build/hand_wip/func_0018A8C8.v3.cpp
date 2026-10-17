// (Claude agent, big8) v3: aligned 106 (v2 111): case 0 hoists INPUT*input=p->input; float amount=input->amount; before the mode test and moving: reuses input (target a0). Function-scope reference/tagTime/mask: no change.
// (Claude agent, big7) v2: fused dot asms (114->111); case 0/1/10/12 func_00140AF8(p,0) path calls func_0018C250(p,5,4) (was a wrong goto idle). Left: 0.15f CSE into f20 (target rematerializes it per call).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
union WORD {int bits;float value;};
struct VE {short delta,pad;void*fn;};
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct INPUT {char pad0[0x1C];float amount;char pad20[0x10];unsigned flags;};
struct ANIMATION {char pad0[0x1C];float localTime;char pad20[0x20];float elapsed;};
struct COMPONENT;struct TAGS;
struct CONTACT {char pad0[0x88];float weight;};
struct GROUP {char pad0[0x80];qword axis;};
struct NODE {char pad0[0xC];VE*vt;char pad10[0x128];void*reference;};
struct CLOCK {float t,dt;};
struct P {
 char pad0[0xC];VE*vt;
 char pad10[0xD8];GROUP*group;
 char padEC[0x64];INPUT*input;
 char pad154[0xB4];CONTACT*contact;float changed;
 char pad210[0x30];qword motion;
 char pad250[0x110];qword flat;
 char pad370[0x158];int gateState;
 char pad4CC[0xB64];ANIMATION*animation;COMPONENT*component;
 char pad1038[0xAC];int kind;
 char pad10E8[0x7DC];NODE*target;
 int mode;float modeTime;int submode;
 char pad18D4[4];int state;float stateTime;ANIMATION*current;int finished;
 char pad18E8[0x19C];TAGS*tags;
 char pad1A88[0x2A8];int enabled;
 char pad1D34[0x260];float factor;WORD gain;
};
struct WORK {U point,local;M3 rotation,returned;U velocity,direction;};
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002BF354,D_002BF360,D_002BF364;
extern qword D_002BF370,D_002A2DA0,D_002A2DC0;
void func_00195A00(void*,int,int,int);
void func_00197500(void*);
void func_001911A8(void*);
void func_001A12F0(void*);
void func_0021F418(void*);
void func_001371C8(void*);
void func_0019E1E0(void*);
int func_00140AF8(P*,int);
unsigned func_00141EA8(P*,int);
int func_001441A0(P*);
int func_001C4660(INPUT*,unsigned,float);
int func_001C46C0(INPUT*,unsigned,float);
void func_001C4738(INPUT*,unsigned);
int func_001938C0(void*,unsigned,int);
void func_0019CC50(void*,int,int,int);
void func_0018C250(P*,int,int);
int func_00131968(ANIMATION*);
int func_001F0638(COMPONENT*);
float func_0012F990(TAGS*,int);
void func_00130D30(ANIMATION*,int,float,float);
int func_00132B10(void*,int);
float func_001E6648(void*);
void func_001E6F10(void*,float,U*,U*);
qword func_001A62E8(void*);
qword func_001A6F00(void*,void*,qword);
M4*func_001A6318(P*);
M3*func_0011B500(M3*,float,qword);
qword func_001D6848(qword,qword,qword,float);
}
static __inline__ void*At(P*p,int offset){return(char*)p+offset;}
static __inline__ void SetMode(P*p,int mode){func_0018C250(p,mode,-1);}
static __inline__ void Joy(P*p,int mode){func_00195A00(At(p,0x2C0),mode,0,0);}
static __inline__ int Can(P*p,int kind){VE&v=p->vt[99];return((int(*)(void*,int))v.fn)((char*)p+v.delta,kind);}
static __inline__ qword Velocity(P*p){VE&v=p->vt[33];return((qword(*)(void*))v.fn)((char*)p+v.delta);}
static __inline__ M4*Frame(NODE*p){VE&v=p->vt[31];return((M4*(*)(void*))v.fn)((char*)p+v.delta);}
static __inline__ void SetVelocity(P*p,qword direction){VE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,direction);}
static __inline__ float Dot(qword a,qword b){
 qword product,one;int bits;float result;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(product),"=&j"(one):"j"(a),"j"(b));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(product));
 __asm__("mtc1 %1,%0":"=f"(result):"r"(bits));
 return result;
}
static __inline__ qword Rotate(qword a,const M3&m){
 __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]));
 return a;
}
static __inline__ qword Point(qword a,const M4&m){
 qword r=m.r[0];
 __asm__("vmulax.xyz $ACC,%0,%1x\n\tvmadday.xyz $ACC,%2,%1y\n\tvmaddaz.xyz $ACC,%3,%1z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(a),"j"(m.r[1]),"j"(m.r[2]),"j"(m.r[3]));
 return r;
}
static __inline__ qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ qword RawScalar(const WORD&word){
 int bits;qword r;
 __asm__("lw %0,%1":"=r"(bits):"m"(word.bits));
 __asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));
 return r;
}
static __inline__ qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ qword Flatten(qword direction,qword axis){
 qword dot,one;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(dot),"=&j"(one):"j"(direction),"j"(axis));
 __asm__("vmulx.xyzw %0,%1,%0x":"+j"(dot):"j"(axis));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(direction):"j"(dot));
 return direction;
}
extern "C" void func_0018A8C8(P*p){
 WORK w;
 int oldMode,oldSub,done;
 void*reference;float tagTime;unsigned mask;INPUT*input;float amount;
 do{
 oldMode=p->mode;
 oldSub=p->submode;
 if((unsigned)oldMode>=25)return;
 switch(oldMode){
 case 7:
  switch(p->gateState){case 1:case 3:case 4:case 12:break;default:goto timer;}
  break;
 case 0:case 1:case 5:case 10:case 11:case 12:case 23:case 24:
  if((unsigned)(p->state-8)<2&&!p->finished)break;
timer:
  if(D_002DDED0.t-p->changed>0.1f)func_00195A00(At(p,0x2C0),0,0,0);
  break;
 default:break;
 }
 if((unsigned)p->mode>=25)return;
 switch(p->mode){
 case 2:
  func_00197500(At(p,0x2C0));
  if(p->enabled){SetMode(p,17);break;}
  if(!Can(p,2))break;
  if(func_001C46C0(p->input,0x80,0.0f)){SetMode(p,13);break;}
  if(func_001C46C0(p->input,0x10,0.0f)){SetMode(p,14);break;}
  break;
 case 7:func_001911A8(At(p,0x4C0));break;
 case 4:func_001A12F0(At(p,0xDF0));break;
 case 23:func_0021F418(At(p,0x11B0));break;
 case 6:func_001371C8(At(p,0x1FF0));break;
 case 8:func_0019E1E0(At(p,0xF50));break;
 case 0:case 1:case 10:case 12:
  if(p->enabled){SetMode(p,17);break;}
  if((unsigned)(p->state-8)<2&&!p->finished)break;
  if(func_001C46C0(p->input,0x40,0.1f)){Joy(p,1);break;}
  if(!(p->input->flags&8)&&func_00140AF8(p,0)){func_0018C250(p,5,4);break;}
  if(func_001C4660(p->input,0x400,0.15f)&&Can(p,3))goto launch;
  if(p->kind==3&&func_001C46C0(p->input,0x20,0.15f)){SetMode(p,11);break;}
  if(func_001C46C0(p->input,0x20,0.2f))goto gate;
  input=p->input;amount=input->amount;
  if(!p->mode){if(amount>0.1f)goto moving;}
  else if(amount>0.0f)goto moving;
  goto idle;
moving:
  if(input->flags&8){SetMode(p,1);break;}
  if(p->kind==3)SetMode(p,10);else SetMode(p,12);
  break;
 case 24:
  if(p->enabled){SetMode(p,17);break;}
  if((float)func_001441A0(p)<=0.0f)goto idle;
  if(func_001C46C0(p->input,0x40,0.1f)){Joy(p,1);break;}
  mask=func_00141EA8(p,0x19);if(!(p->input->flags&mask))goto idle;
  if(p->submode!=13)break;
  w.velocity.q=Velocity(p);
  if(Dot(w.velocity.q,func_001A6318(p)->r[0])<D_002BF354)goto idle;
  break;
 case 5:
  if(p->enabled){SetMode(p,17);break;}
  if((unsigned)(p->submode-6)<4)break;
  if((p->input->flags&8)||!func_00140AF8(p,1))goto idle;
  if(func_001C46C0(p->input,0x40,0.1f)){Joy(p,1);break;}
  if(func_001C4660(p->input,0x400,0.15f)&&Can(p,3)){
launch:
   func_001C4738(p->input,0x400);
   func_0019CC50(At(p,0xF00),0,0,0);break;
  }
  if(func_001C46C0(p->input,0x20,0.2f)){
gate:
   (void)func_001938C0(At(p,0x4C0),0xFFFF,0);break;
  }
  if(p->input->amount>0.0f)func_0018C250(p,5,5);
  else func_0018C250(p,5,4);
  break;
 case 3:
  if(D_002DDED0.t-p->modeTime>0.25f&&func_001C46C0(p->input,0x40,0.25f)){Joy(p,2);break;}
  break;
 case 13:
  if(func_00131968(p->animation)){Joy(p,11);break;}
  if(!p->contact)break;
  if(p->contact->weight>0.7f){if(D_002DDED0.t-p->modeTime>0.4f)goto seekTime;}
  break;
 case 14:
  if(func_00131968(p->animation))goto idle;
seek:
  if(p->contact&&p->contact->weight>0.7f&&D_002DDED0.t-p->modeTime>0.4f){
seekTime:
   tagTime=func_0012F990(p->tags,0x16D);
   if(p->animation->localTime<tagTime)func_00130D30(p->animation,0,tagTime,p->animation->elapsed);
  }
  break;
 case 16:
  if(!p->animation)goto idle;
  done=func_00131968(p->animation);
checkDone:
  if(done)goto idle;
  break;
 case 19:
  if(p->animation){done=func_00131968(p->animation);if(done)goto idle;}
  if(!p->component)break;
  done=func_001F0638(p->component);goto checkDone;
 case 17:
  if(p->enabled){if(D_002DDED0.t-p->modeTime>D_002BF360)goto idle;break;}
idle:
  SetMode(p,0);break;
 case 21:
  if(!func_001C46C0(p->input,0x40,0.25f))break;
  Joy(p,18);break;
 case 22:{
  if(!func_001C46C0(p->input,0x40,0.25f))break;
  reference=p->target->reference;
  if(reference&&func_00132B10(reference,10)){
   reference=p->target->reference;
   float length=func_001E6648(reference);
   func_001E6F10(reference,length*(0.5f-p->factor*0.5f),&w.point,0);
  }else{
   reference=p->target->reference;
   w.local.q=reference?func_001A6F00(0,p->target,func_001A62E8(reference)):D_002BF370;
   (void)func_0011B500(&w.returned,p->factor*D_002BF364,D_002A2DA0);
   w.rotation=w.returned;
   M4*frame=Frame(p->target);
   w.point.q=Point(Rotate(w.local.q,w.rotation),*frame);
  }
  qword current=func_001A62E8(p);
  w.direction.q=func_001D6848(current,Sub(w.point.q,p->motion),p->group->axis,0.5f);
  w.local.q=RawScalar(p->gain);
  SetVelocity(p,Scale(w.direction.q,w.local.q));
  func_00195A00(At(p,0x2C0),12,0,0);
  p->flat=Flatten(w.direction.q,D_002A2DC0);
  break;
 }
 default:break;
 }
 }while(p->mode!=oldMode||p->submode!=oldSub);
 return;
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_WORD[(sizeof(WORD)==4)?1:-1];
typedef char layout_VE[(sizeof(VE)==8)?1:-1];
typedef char layout_M3[(sizeof(M3)==0x30)?1:-1];
typedef char layout_M4[(sizeof(M4)==0x40)?1:-1];
typedef char layout_WORK[(sizeof(WORK)==0xA0)?1:-1];
typedef char layout_INPUT[(sizeof(INPUT)==0x34)?1:-1];
typedef char layout_ANIMATION[(sizeof(ANIMATION)==0x44)?1:-1];
typedef char layout_CONTACT[(sizeof(CONTACT)==0x8C)?1:-1];
typedef char layout_GROUP[(sizeof(GROUP)==0x90)?1:-1];
typedef char layout_NODE[(sizeof(NODE)==0x13C)?1:-1];
typedef char layout_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_P[(sizeof(P)==0x1FA0)?1:-1];
typedef char layout_VE_delta[((unsigned long)&((VE*)0)->delta==0x0)?1:-1];
typedef char layout_VE_fn[((unsigned long)&((VE*)0)->fn==0x4)?1:-1];
typedef char layout_U_q[((unsigned long)&((U*)0)->q==0x0)?1:-1];
typedef char layout_U_f[((unsigned long)&((U*)0)->f==0x0)?1:-1];
typedef char layout_WORD_bits[((unsigned long)&((WORD*)0)->bits==0x0)?1:-1];
typedef char layout_WORD_value[((unsigned long)&((WORD*)0)->value==0x0)?1:-1];
typedef char layout_INPUT_amount[((unsigned long)&((INPUT*)0)->amount==0x1c)?1:-1];
typedef char layout_INPUT_flags[((unsigned long)&((INPUT*)0)->flags==0x30)?1:-1];
typedef char layout_ANIMATION_localTime[((unsigned long)&((ANIMATION*)0)->localTime==0x1c)?1:-1];
typedef char layout_ANIMATION_elapsed[((unsigned long)&((ANIMATION*)0)->elapsed==0x40)?1:-1];
typedef char layout_CONTACT_weight[((unsigned long)&((CONTACT*)0)->weight==0x88)?1:-1];
typedef char layout_GROUP_axis[((unsigned long)&((GROUP*)0)->axis==0x80)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_reference[((unsigned long)&((NODE*)0)->reference==0x138)?1:-1];
typedef char layout_CLOCK_t[((unsigned long)&((CLOCK*)0)->t==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_WORK_point[((unsigned long)&((WORK*)0)->point==0x0)?1:-1];
typedef char layout_WORK_local[((unsigned long)&((WORK*)0)->local==0x10)?1:-1];
typedef char layout_WORK_rotation[((unsigned long)&((WORK*)0)->rotation==0x20)?1:-1];
typedef char layout_WORK_returned[((unsigned long)&((WORK*)0)->returned==0x50)?1:-1];
typedef char layout_WORK_velocity[((unsigned long)&((WORK*)0)->velocity==0x80)?1:-1];
typedef char layout_WORK_direction[((unsigned long)&((WORK*)0)->direction==0x90)?1:-1];
typedef char layout_P_vt[((unsigned long)&((P*)0)->vt==0xc)?1:-1];
typedef char layout_P_group[((unsigned long)&((P*)0)->group==0xe8)?1:-1];
typedef char layout_P_input[((unsigned long)&((P*)0)->input==0x150)?1:-1];
typedef char layout_P_contact[((unsigned long)&((P*)0)->contact==0x208)?1:-1];
typedef char layout_P_changed[((unsigned long)&((P*)0)->changed==0x20c)?1:-1];
typedef char layout_P_motion[((unsigned long)&((P*)0)->motion==0x240)?1:-1];
typedef char layout_P_flat[((unsigned long)&((P*)0)->flat==0x360)?1:-1];
typedef char layout_P_gateState[((unsigned long)&((P*)0)->gateState==0x4c8)?1:-1];
typedef char layout_P_animation[((unsigned long)&((P*)0)->animation==0x1030)?1:-1];
typedef char layout_P_component[((unsigned long)&((P*)0)->component==0x1034)?1:-1];
typedef char layout_P_kind[((unsigned long)&((P*)0)->kind==0x10e4)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x18c4)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x18c8)?1:-1];
typedef char layout_P_modeTime[((unsigned long)&((P*)0)->modeTime==0x18cc)?1:-1];
typedef char layout_P_submode[((unsigned long)&((P*)0)->submode==0x18d0)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d8)?1:-1];
typedef char layout_P_stateTime[((unsigned long)&((P*)0)->stateTime==0x18dc)?1:-1];
typedef char layout_P_current[((unsigned long)&((P*)0)->current==0x18e0)?1:-1];
typedef char layout_P_finished[((unsigned long)&((P*)0)->finished==0x18e4)?1:-1];
typedef char layout_P_tags[((unsigned long)&((P*)0)->tags==0x1a84)?1:-1];
typedef char layout_P_enabled[((unsigned long)&((P*)0)->enabled==0x1d30)?1:-1];
typedef char layout_P_factor[((unsigned long)&((P*)0)->factor==0x1f94)?1:-1];
typedef char layout_P_gain[((unsigned long)&((P*)0)->gain==0x1f98)?1:-1];
