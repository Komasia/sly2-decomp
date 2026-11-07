#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
struct VTE {short delta,pad;void*fn;};
struct PL {char pad[0x1C];float amount;char pad20[0x10];unsigned flags;};
struct CONTROL {int word0,state;char pad8[0x14];int count;};
struct GATE {int word0,word4,mode;};
struct P {char pad[0xC];VTE*vt;char pad10[0x140];PL*input;char pad154[0xB8];float changed;char pad210[0xB0];CONTROL control;char pad2E0[0x1E0];GATE gate;char pad4CC[0x924];char action[0x110];char altAction[0x50];char physics[0xE0];void*animation;void*other;char pad1038[0x398];int state;char pad13D4[0x14];int pending;void*root;char pad13F0[0x5C];int flag;char pad1450[0x3F0];int kind;char pad1844[0xCC];char extra[1];};
struct CLOCK {float time,dt;};
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char PL_Size[sizeof(PL)==52?1:-1];
typedef char CONTROL_Size[sizeof(CONTROL)==32?1:-1];
typedef char GATE_Size[sizeof(GATE)==12?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char PL_amount_Offset[FIELD_OFFSET(PL,amount)==28?1:-1];
typedef char PL_flags_Offset[FIELD_OFFSET(PL,flags)==48?1:-1];
typedef char CONTROL_state_Offset[FIELD_OFFSET(CONTROL,state)==4?1:-1];
typedef char CONTROL_count_Offset[FIELD_OFFSET(CONTROL,count)==28?1:-1];
typedef char GATE_mode_Offset[FIELD_OFFSET(GATE,mode)==8?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_input_Offset[FIELD_OFFSET(P,input)==336?1:-1];
typedef char P_changed_Offset[FIELD_OFFSET(P,changed)==524?1:-1];
typedef char P_control_Offset[FIELD_OFFSET(P,control)==704?1:-1];
typedef char P_gate_Offset[FIELD_OFFSET(P,gate)==1216?1:-1];
typedef char P_action_Offset[FIELD_OFFSET(P,action)==3568?1:-1];
typedef char P_altAction_Offset[FIELD_OFFSET(P,altAction)==3840?1:-1];
typedef char P_physics_Offset[FIELD_OFFSET(P,physics)==3920?1:-1];
typedef char P_animation_Offset[FIELD_OFFSET(P,animation)==4144?1:-1];
typedef char P_other_Offset[FIELD_OFFSET(P,other)==4148?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(P,state)==5072?1:-1];
typedef char P_pending_Offset[FIELD_OFFSET(P,pending)==5096?1:-1];
typedef char P_root_Offset[FIELD_OFFSET(P,root)==5100?1:-1];
typedef char P_flag_Offset[FIELD_OFFSET(P,flag)==5196?1:-1];
typedef char P_kind_Offset[FIELD_OFFSET(P,kind)==6208?1:-1];
typedef char P_extra_Offset[FIELD_OFFSET(P,extra)==6416?1:-1];
extern "C" CLOCK g_clock;
extern "C" float D_002C08DC,D_002C08E0;
extern "C" void SetJumpKind(void*,int,void*,void*) asm("SetJumpKind__FP4JUMPiiP2LO");
extern "C" void OpenBinoc(void*,int,void*,void*) asm("OpenBinoc__FP5ACTORiP2LOT2");
extern "C" int FActorTargetInReach(P*,int) asm("FActorTargetInReach__FP5ACTORi");
extern "C" void func_001B6078(P*,int);
extern "C" unsigned GrfPadctlTakePressed(PL*,unsigned,float) asm("GrfPadctlTakePressed__FP6PADCTL");
extern "C" unsigned GrfPadctlPressedWithin(PL*,unsigned,float) asm("GrfPadctlPressedWithin__FP6PADCTLUif");
extern "C" void ForgetPadctlPresses(PL*,int) asm("ForgetPadctlPresses__FP6PADCTLUi");
extern "C" int func_001B84E0(P*);
extern "C" void func_001B85D0(P*);
extern "C" void StartMurrayPunch(P*) asm("StartMurrayPunch__FP6MURRAY");
extern "C" int FMurrayGrab(P*) asm("FMurrayGrab__FP6MURRAY");
extern "C" int FInteractCircle(void*,unsigned,int) asm("FInteractCircle__FP5ACTOR");
extern "C" void UpdateJumpTransitions(void*) asm("UpdateJumpTransitions__FP4JUMP");
extern "C" int FActorBelowFloorSoon(P*,float) asm("FActorBelowFloorSoon__FP5ACTORf");
extern "C" void UpdateInteractTransitions(void*) asm("UpdateInteractTransitions__FP5ACTOR");
extern "C" void UpdateDamageTransitions(void*) asm("UpdateDamageTransitions__FP5ACTOR");
extern "C" void UpdateMurrayFlop(P*) asm("UpdateMurrayFlop__FP6MURRAY");
extern "C" void UpdateMurrayCarryHeld(P*) asm("UpdateMurrayCarryHeld__FP6MURRAY");
extern "C" void UpdateMurrayHold(P*) asm("UpdateMurrayHold__FP6MURRAY");
extern "C" void UpdateMurrayCarryTransitions(P*) asm("UpdateMurrayCarryTransitions__FP6MURRAY");
extern "C" int func_00131968(void*);
extern "C" int func_001F0638(void*);
extern "C" void UpdateMurrayPunchTransitions(P*) asm("UpdateMurrayPunchTransitions__FP6MURRAY");
extern "C" void UpdateMurrayBehavior(P*) asm("UpdateMurrayBehavior__FP6MURRAY");
extern "C" void UpdateMurrayBerserkTransitions(P*) asm("UpdateMurrayBerserkTransitions__FP6MURRAY");
extern "C" void UpdateJtThrow(void*) asm("UpdateJtThrow__FP7JTTHROW");
extern "C" void UpdateClimbTransitions(void*) asm("UpdateClimbTransitions__FP5ACTOR");
extern "C" int func_00141EA8(P*,int);
static inline PL*CopyPL(PL*source){PL*result;__asm__("daddu %0,%1,$zero":"=r"(result):"r"(source));return result;}
static inline int Can(P*p,int kind){return ((int(*)(void*,int))p->vt[99].fn)((char*)p+p->vt[99].delta,kind);}
// name: SafeHouse port (UpdateMurrayTransitions)
extern "C" void UpdateMurrayTransitions__FP6MURRAY(P*p){
 int state;
 do{
  state=p->state;
  switch(state){
  case 2:case 3:case 4:case 6:case 7:case 8:case 14:case 15:case 16:case 17:case 18:case 20:break;
  default:
   if(g_clock.time-p->changed>0.1f){
    switch(p->state){
    case 5:SetJumpKind(&p->control,16,0,0);break;
    case 12:if(p->kind==3)SetJumpKind(&p->control,11,0,0);break;
    case 13:if(p->gate.mode!=1&&p->gate.mode!=12)SetJumpKind(&p->control,0,0,0);break;
    default:SetJumpKind(&p->control,0,0,0);break;
    }
   }
  }
  int finished;
  switch(p->state){
  case 0:case 1:case 10:{
   if(!(p->input->flags&8)&&FActorTargetInReach(p,0)){func_001B6078(p,9);break;}
   if(GrfPadctlTakePressed(p->input,0x40,0.1f)){SetJumpKind(&p->control,1,0,0);break;}
   if(GrfPadctlPressedWithin(p->input,0x400,0.15f)&&Can(p,3)){
    ForgetPadctlPresses(p->input,0x400);
    OpenBinoc(p->altAction,0,0,0);
    break;
   }
   if(func_001B84E0(p)&&GrfPadctlTakePressed(p->input,0x10,D_002C08DC)){func_001B85D0(p);break;}
   if(FMurrayGrab(p))break;
   if(GrfPadctlTakePressed(p->input,0x20,0.2f)){
    if(!FInteractCircle(&p->gate,0xF8FA,0)&&p->root){p->flag=0;func_001B6078(p,4);}
    break;
   }
   if(func_001B84E0(p)&&GrfPadctlTakePressed(p->input,0x80,D_002C08DC)){StartMurrayPunch(p);break;}
   PL*input=p->input;PL*flagsInput=CopyPL(input);register int current __asm__("$3")=p->state;
   if(current==0){if(input->amount>0.1f)goto moving;}
   else if(input->amount>0.0f)goto moving;
   goto idle;
  moving:
   if(flagsInput->flags&8)func_001B6078(p,1);else func_001B6078(p,10);
   break;
  }
  case 2:
   UpdateJumpTransitions(&p->control);
   switch(p->control.state){case 0:case 11:case 15:case 16:break;
   default:
    if(GrfPadctlPressedWithin(p->input,0x90,D_002C08DC)&&Can(p,2)&&p->control.count<6&&p->control.count>0&&!FActorBelowFloorSoon(p,D_002C08E0)){
     ForgetPadctlPresses(p->input,0x90);
     p->pending=0;
     func_001B6078(p,3);
    }
   }
   break;
  case 13:UpdateInteractTransitions(&p->gate);break;
  case 14:UpdateDamageTransitions(p->action);break;
  case 3:UpdateMurrayFlop(p);break;
  case 5:UpdateMurrayCarryHeld(p);break;
  case 6:UpdateMurrayHold(p);break;
  case 4:UpdateMurrayCarryTransitions(p);break;
  case 7:case 8:finished=func_00131968(p->animation);goto checkIdle;
  case 11:UpdateMurrayPunchTransitions(p);break;
  case 9:UpdateMurrayBehavior(p);break;
  case 12:UpdateMurrayBerserkTransitions(p);break;
  case 15:UpdateJtThrow(p->extra);break;
  case 20:UpdateClimbTransitions(p->physics);break;
  case 17:
   if(p->animation&&func_00131968(p->animation))goto idle;
   if(!p->other)break;
   finished=func_001F0638(p->other);
  checkIdle:
   if(!finished)break;
  idle:
   func_001B6078(p,0);
   break;
  case 21:
   if(GrfPadctlTakePressed(p->input,0x40,0.0f))SetJumpKind(&p->control,13,0,0);
   else if(!(p->input->flags&func_00141EA8(p,0x10)))func_001B6078(p,0);
   break;
  default:break;
  }
 }while(p->state!=state);
}
