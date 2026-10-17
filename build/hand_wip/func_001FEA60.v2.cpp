class X;
typedef void (X::*PMF)();
struct P {char pad0[0x13C];float weights[8][4];int pad1BC;float outputs[4];char pad1D0[0x30];X *object;int count;X *refs[8];X *component;};
struct LM {float low,high;};
extern LM D_002BBB60;
extern PMF D_002A8298,D_002A82A0;
extern "C" float func_0011D948(LM *,float);
extern "C" void *func_002333B4(void *,int,unsigned int);
extern "C" void func_002321E8(int,int);
extern "C" void func_001FEA60(P *p,int channel,int category,float input)
{
    if((unsigned int)category>=8)return;
    if(channel<0)return;
    if(channel>=4)return;
    input=func_0011D948(&D_002BBB60,input);
    float (*w)[4]=p->weights;
    if(p->weights[category][channel]==input)return;
    if(category==2){
        PMF action;
        func_002333B4(&action,0,8);
        if(input==0.0f)action=D_002A8298;
        else if(w[2][channel]==0.0f)action=D_002A82A0;
        if(action!=0){
            switch(channel){
            case 0:if(p->component)(p->component->*action)();break;
            case 1:for(int i=0;i<p->count;i++){X **pp=&p->refs[i];if(*pp)((*pp)->*action)();}break;
            case 2:if(p->object)(p->object->*action)();break;
            }
        }
    }
    p->weights[category][channel]=input;
    input=1.0f;
    for(int i=0;i<8;i++)input*=p->weights[i][channel];
    int next=(int)(input*1024.0f);
    if((int)(p->outputs[channel]*1024.0f)!=next){
        p->outputs[channel]=input;
        func_002321E8(channel,next);
    }
}
