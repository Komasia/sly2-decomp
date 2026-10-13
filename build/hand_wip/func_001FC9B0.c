typedef int qword __attribute__((mode(TI)));
struct LO {char pad28[0x28];unsigned long flags;};
struct E {struct LO *object;float angle;int unused;float gain;};
struct P {char pad1C[0x1C];struct LO *object;qword position;char pad30[0x70];int counts[6];struct E entries[6][8];};
extern qword D_002A2DD0;
int func_0011D4D0(float,float,float);
void func_001FB528(struct P *);
qword func_001A62E8(struct LO *);
void func_001FB778(struct P *,qword,float *,float *,int *);
void func_001FC380(struct P *,int,int);
void func_001FC2E0(struct P *,int,float);
static __inline__ float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static __inline__ float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static __inline__ float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
void func_001FC9B0(struct P *p)
{
    int group;
    if(!p->object){
        qword value=p->position;
        qword reference=D_002A2DD0;
        int same=0;
        if(func_0011D4D0(X(reference),X(value),0.0001f) &&
           func_0011D4D0(Y(reference),Y(value),0.0001f) &&
           func_0011D4D0(Z(reference),Z(value),0.0001f))same=1;
        if(!same)func_001FB528(p);
    }
    for(group=0;group<6;group++){
        int remaining=p->counts[group];
        if(remaining){
            float maximum=0.0f;
            int flags=0,active=0;
            int *pflags=&flags;
            struct E *entry=&p->entries[group][0];
            float *angle=&entry->angle;
            float fade;
            if(remaining>0){
                while(remaining--){
                    struct LO *object=entry->object;
                    if(object && ((object->flags>>60)&1)){
                        qword pos;
                        ++active;
                        pos=func_001A62E8(object);
                        func_001FB778(p,pos,angle,&fade,pflags);
                        pflags=0;
                        {float gain=fade*entry->gain;maximum=maximum>gain?maximum:gain;}
                    }
                    ++entry;angle+=4;
                }
            }
            func_001FC380(p,group,active==1?flags:0);
            func_001FC2E0(p,group,maximum);
        }
    }
}
