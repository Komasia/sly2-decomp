struct S {
    char pad[0x58]; int state; float time; int tick; int mode; float update;
    char pad1[4]; int id0; int id1; int id2; int selected; int x80; void *sprite; float animtime; float duration;
    char pad2[0xA4-0x90]; int flag; char pad3[8]; int pauses;
};
struct Clock { char pad[0x3C]; float time; float dt; };
extern struct Clock g_clock;
extern float D_002DDF10;
void UpdateLo__FP2LO(struct S *);
int FSpriteAnimPlaying__FP2LOi(struct S *,int);
void SetTimerTimers(struct S *,int) asm("SetTimerTimers__FP5TIMER6TIMERS");
void SetState__FP8SCREENRTi(struct S *,int);
void func_00218220(void *,float);
void func_00212C50(struct S *p) {
    int state;
    UpdateLo__FP2LO(p);
    state=p->state;
    if(state==1) {
        if(p->mode==2) state=p->id1==-1 ? 2:3;
    } else if(p->update != g_clock.time) {
        switch(state) {
        case 2:
            if(!FSpriteAnimPlaying__FP2LOi(p,p->selected)) SetTimerTimers(p,1);
            if(p->duration>0.0f && p->duration<g_clock.time-p->time) SetTimerTimers(p,1);
            if(p->mode==1) state=p->id2==-1 ? 1:4;
            break;
        case 3:
            if(!FSpriteAnimPlaying__FP2LOi(p,p->id1)) {
                switch(p->mode) {
                case 1: state=p->id2==-1 ? 1:4; break;
                case 2: state=2; break;
                }
            }
            break;
        case 4:
            if(!FSpriteAnimPlaying__FP2LOi(p,p->id2)) {
                switch(p->mode) {
                case 1: state=1; break;
                case 2: state=p->id1==-1 ? 2:3; break;
                }
            }
            break;
        }
    }
    SetState__FP8SCREENRTi(p,state);
    if(p->selected!=-1) {
        float dt=D_002DDF10;
        p->animtime+=dt;
        func_00218220(p->sprite,dt);
    }
}
