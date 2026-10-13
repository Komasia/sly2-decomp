// Select and normalize three animation blend weights.
extern "C" {
struct REF {char pad50[0x50];unsigned short flags,state;};
struct COEF {float a,b,c;};
struct PLAYER {char pad4C8[0x4C8];int action;char pad4CC[0xBFC];int mode;char pad10CC[0x20];int state;};
struct P {char pad5C[0x5C];int modeA,modeB,selected;char pad68[0xA0];float weights[3];struct COEF coefficients[3];char pad138[0xCC];int count;struct REF *refs[8];};
struct CLOCK {float time,dt;};
extern char D_003DD490[];
extern struct CLOCK D_002DDED0;
struct PLAYER *func_001C4A48(void *);
int func_00132B10(void *,int);
float func_0011D018(float,float,float,struct COEF *,float *);
void func_001FC2E0(struct REF *,int,float);
static __inline__ float Sqrt(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
void func_001FDC08(struct P *input)
{
    register struct P *p __asm__("$17")=input;
    struct REF *ref;
    float *weights;
    int i;
    float sum,selectedSquare;
    p->selected=1;
    if(p->modeA)p->selected=2;
    else if(p->modeB)p->selected=0;
    else if(func_001C4A48(D_003DD490) && func_00132B10(func_001C4A48(D_003DD490),0x34)){
        struct PLAYER *player=func_001C4A48(D_003DD490);
        if(player->state==3)p->selected=2;
        else if(player->state==4)p->selected=2;
        else if(player->mode!=-1)p->selected=0;
        else if(player->action>=0){if(player->action<3 || player->action==13)p->selected=0;}
    }
    if(p->count>0)ref=((struct REF **)&p->count)[p->count];else ref=0;
    int locked=ref && !ref->state && ((ref->flags&1)!=0);
    weights=p->weights;
    if(locked)weights[p->selected]=1.0f;
    else weights[p->selected]=func_0011D018(weights[p->selected],1.0f,D_002DDED0.dt,&p->coefficients[p->selected],0);
    sum=0.0f;selectedSquare=weights[p->selected]*weights[p->selected];
    for(i=0;i<3;i++)if(i!=p->selected)sum+=weights[i]*weights[i];
    if(sum<0.0001f){
        for(i=0;i<3;i++){
            if(i==p->selected)weights[i]=1.0f;else weights[i]=0.0f;
        }
    }else{
        float gain=Sqrt((1.0f-selectedSquare)/sum);
        for(i=0;i<3;i++)if(i!=p->selected)weights[i]*=gain;
    }
    if(ref){func_001FC2E0(ref,0,p->weights[0]);func_001FC2E0(ref,1,p->weights[1]);func_001FC2E0(ref,2,p->weights[2]);}
}

}
