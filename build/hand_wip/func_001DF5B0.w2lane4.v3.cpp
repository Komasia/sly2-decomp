typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int bits[4];};
struct M3 {U rows[3];};
struct M4 {U rows[4];};
union PHASE {struct {M3 facing;M4 render,output;} initial;struct {M4 matrix,output;} endpoint;};
struct DISTANCE {float value;};
struct MEASUREMENT {DISTANCE distance;U direction;};
struct ENTRY {char pad0[0x144];float maximumLength;char pad148[8];};
struct CONFIG {char pad0[0x1C];float first;char pad20[0x20];float second;};
struct VENTRY {short delta,pad;void (*fn)(void *,U *,int,float,float);};
struct HOOK {VENTRY *vt;};
struct ENDPOINT {void *object;int unused4;CONFIG *config;HOOK *scale;};
struct BOUND {char pad0[0x20];U position;float radius;};
struct P {char pad0[0xEC];BOUND *bound;char padF0[0xA0];void *line,*stretch;int count;ENTRY *entries;ENDPOINT endpoints[2];};
struct CAMERA {char pad0[0x90];U position;};
extern CAMERA D_002DDF40;
extern const qword D_002A2DC0;
extern "C" {
void func_001F3C70(P *);
int func_0014F850(CAMERA *,qword,qword);
void func_001DEF98(P *,ENTRY *,qword *,float *);
void func_001A5FB8(void *,qword,qword,float,float);
M3 *func_0011B830(M3 *,qword,qword);
M4 *func_0011C210(M4 *,qword,const M3 *,const U *);
qword *func_00256D18(qword *,qword);
void func_001A5EE8(void *,const M4 *,float,float);
}
struct ENDPOINT_MATRIX: M4 {};
static inline M4*EndpointCopy(M4&destination,const M4&source){
 qword a=source.rows[0].q,b=source.rows[1].q,c=source.rows[2].q,d=source.rows[3].q;
 destination.rows[0].q=a;destination.rows[1].q=b;destination.rows[2].q=c;destination.rows[3].q=d;return &destination;
}
static inline M4*EndpointFacing(M4&destination,const M3&basis,qword position){
 func_00256D18(&destination.rows[3].q,position);
 destination.rows[0]=basis.rows[0];destination.rows[1]=basis.rows[1];destination.rows[2]=basis.rows[2];
 destination.rows[0].bits[3]=destination.rows[1].bits[3]=destination.rows[2].bits[3]=0;
 destination.rows[3].f[3]=1.0f;return &destination;
}
static inline void CopyMatrix(M4&destination,const M4&source){qword a=source.rows[0].q,b=source.rows[1].q,c=source.rows[2].q,d=source.rows[3].q;destination.rows[0].q=a;destination.rows[1].q=b;destination.rows[2].q=c;destination.rows[3].q=d;}
static inline void CopyBasis(M3&destination,const M3&source){destination=source;}
static inline qword BroadcastInto(float value,U&home){qword result;__asm__("qmtc2.ni %1,%0":"=j"(result):"r"(value));home.q=result;return home.q;}
static inline qword Scalar(const float *p){qword r;__asm__("":"=r"(r):"0"(*(const int *)p));return r;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword PublishDirectionAndReadAxis(U&home,qword direction,const qword&axis){home.q=direction;return axis;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(const U&value){qword d,one;float r;__asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x ACC,%0,%0y
	vmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(value.q));__asm__("vsqrt Q,%0x
	vwaitq
	vaddq.x %0,$vf0,Q":"+j"(d));__asm__("mtc1 %1,%0":"=f"(r):"r"(d));return r;}
static inline int ElementOffset(int index){return index*(int)sizeof(ENTRY);}
static inline void Query(P*owner,ENTRY*entry,U(&points)[2],DISTANCE&distance){func_001DEF98(owner,entry,&points[0].q,&distance.value);}
extern "C" void func_001DF5B0(P *p)
{
    U scalar,points[2];
    M3 basis;
    PHASE workspace;
    MEASUREMENT measurement;
    func_001F3C70(p);
    BOUND *bound = p->bound;
    if(!bound)return;
    scalar.q=Scalar(&bound->radius);
    qword relativePosition=Subtract(bound->position.q,D_002DDF40.position.q);
    if(!func_0014F850(&D_002DDF40,relativePosition,scalar.q))return;
    for(int i=0;i<p->count;){
        ENTRY *entry=(ENTRY*)((char*)p->entries+ElementOffset(i));
        Query(p,entry,points,measurement.distance);
        if(entry->maximumLength<measurement.distance.value){
            float ratio=entry->maximumLength/measurement.distance.value;
            points[1].q=Add(Scale(points[0].q,BroadcastInto(1.0f-ratio,scalar)),Scale(points[1].q,BroadcastInto(ratio,scalar)));
        }
        if(p->line)func_001A5FB8(p->line,points[0].q,points[1].q,1.0f,1.0f);
        if(p->stretch||p->endpoints[0].object||p->endpoints[1].object){
            qword axis=PublishDirectionAndReadAxis(measurement.direction,
                Subtract(points[1].q,points[0].q),D_002A2DC0);
            func_0011B830(&workspace.initial.facing,measurement.direction.q,axis);
            CopyBasis(basis,workspace.initial.facing);
        }
        if(p->stretch){
            float length=Length(measurement.direction);
            if(0.01f<length){
                scalar.f[0]=length*0.01f;
                scalar.f[1]=1.0f;
                scalar.f[2]=1.0f;
                func_0011C210(&workspace.initial.output,points[0].q,&basis,&scalar);
                CopyMatrix(workspace.initial.render,workspace.initial.output);
                func_001A5EE8(p->stretch,&workspace.initial.render,1.0f,1.0f);
            }
        }
        int next=i+1;
        for(unsigned int j=0;j<2;j++){
            ENDPOINT *end=&p->endpoints[j];
            if(end->object){
                M4 *transform;
                if(end->scale){
                    HOOK *scale=end->scale;
                    VENTRY &callback=scale->vt[3];
                    callback.fn((char *)scale+callback.delta,&scalar,0,end->config->first,end->config->second);
                    func_0011C210(&workspace.endpoint.output,points[j].q,&basis,&scalar);
                    transform=EndpointCopy(workspace.endpoint.matrix,workspace.endpoint.output);
                }else{
                    transform=EndpointFacing(workspace.endpoint.matrix,basis,points[j].q);
                }
                func_001A5EE8(end->object,transform,1.0f,1.0f);
            }
        }
        i=next;
    }
}

typedef char connector_physical_0[(((unsigned int)&((ENTRY*)0)->maximumLength)==324)?1:-1];
typedef char connector_physical_1[(((unsigned int)&((P*)0)->bound)==236)?1:-1];
typedef char connector_physical_2[(((unsigned int)&((P*)0)->line)==400)?1:-1];
typedef char connector_physical_3[(((unsigned int)&((P*)0)->stretch)==404)?1:-1];
typedef char connector_physical_4[(((unsigned int)&((P*)0)->count)==408)?1:-1];
typedef char connector_physical_5[(((unsigned int)&((P*)0)->entries)==412)?1:-1];
typedef char connector_physical_6[(((unsigned int)&((P*)0)->endpoints)==416)?1:-1];
typedef char connector_physical_7[(((unsigned int)&((BOUND*)0)->position)==32)?1:-1];
typedef char connector_physical_8[(((unsigned int)&((BOUND*)0)->radius)==48)?1:-1];
typedef char connector_physical_9[(((unsigned int)&((CAMERA*)0)->position)==144)?1:-1];
typedef char connector_physical_10[(((unsigned int)&((ENDPOINT*)0)->object)==0)?1:-1];
typedef char connector_physical_11[(((unsigned int)&((ENDPOINT*)0)->config)==8)?1:-1];
typedef char connector_physical_12[(((unsigned int)&((ENDPOINT*)0)->scale)==12)?1:-1];
typedef char connector_physical_13[(((unsigned int)&((CONFIG*)0)->first)==28)?1:-1];
typedef char connector_physical_14[(((unsigned int)&((CONFIG*)0)->second)==64)?1:-1];
typedef char connector_physical_15[(((unsigned int)&((HOOK*)0)->vt)==0)?1:-1];
typedef char connector_physical_16[(((unsigned int)&((VENTRY*)0)->delta)==0)?1:-1];
typedef char connector_physical_17[(((unsigned int)&((VENTRY*)0)->fn)==4)?1:-1];
typedef char connector_physical_18[(((unsigned int)&((DISTANCE*)0)->value)==0)?1:-1];
typedef char connector_physical_19[(((unsigned int)&((PHASE*)0)->initial.facing)==0)?1:-1];
typedef char connector_physical_20[(((unsigned int)&((PHASE*)0)->initial.render)==48)?1:-1];
typedef char connector_physical_21[(((unsigned int)&((PHASE*)0)->initial.output)==112)?1:-1];
typedef char connector_physical_22[(((unsigned int)&((PHASE*)0)->endpoint.matrix)==0)?1:-1];
typedef char connector_physical_23[(((unsigned int)&((PHASE*)0)->endpoint.output)==64)?1:-1];
typedef char connector_physical_24[(sizeof(U)==16)?1:-1];
typedef char connector_physical_25[(sizeof(M3)==48)?1:-1];
typedef char connector_physical_26[(sizeof(M4)==64)?1:-1];
typedef char connector_physical_27[(sizeof(ENTRY)==336)?1:-1];
typedef char connector_physical_28[(sizeof(ENDPOINT)==16)?1:-1];
typedef char connector_physical_29[(sizeof(VENTRY)==8)?1:-1];
typedef char connector_physical_30[(sizeof(DISTANCE)==4)?1:-1];
typedef char connector_physical_31[(sizeof(PHASE)==176)?1:-1];
typedef char connector_physical_32[(sizeof(int)==4)?1:-1];
typedef char connector_physical_33[(sizeof(qword)==16)?1:-1];
typedef char connector_physical_34[(sizeof(MEASUREMENT)==32)?1:-1];
typedef char connector_physical_35[(((unsigned int)&((MEASUREMENT*)0)->distance)==0)?1:-1];
typedef char connector_physical_36[(((unsigned int)&((MEASUREMENT*)0)->direction)==16)?1:-1];
typedef char connector_physical_37[(__alignof__(MEASUREMENT)==16)?1:-1];
typedef char connector_physical_38[(sizeof(float)==4)?1:-1];
typedef char connector_physical_39[(sizeof(void*)==4)?1:-1];
typedef char connector_physical_40[(__alignof__(U)==16)?1:-1];
typedef char connector_physical_41[(sizeof(BOUND*)==4)?1:-1];
typedef char connector_physical_42[(((unsigned int)&((M4*)0)->rows[3])==48)?1:-1];
typedef char connector_physical_43[(((unsigned int)&((M3*)0)->rows[2])==32)?1:-1];
typedef char connector_physical_44[(sizeof(((M4*)0)->rows)==64)?1:-1];
typedef char connector_physical_45[(sizeof(((M3*)0)->rows)==48)?1:-1];
typedef char connector_physical_46[(sizeof(ENDPOINT_MATRIX)==64)?1:-1];
typedef char connector_physical_47[(__alignof__(ENDPOINT_MATRIX)==16)?1:-1];
typedef char connector_physical_48[(((unsigned int)&((ENDPOINT_MATRIX*)0)->rows[0])==0)?1:-1];
typedef char connector_physical_49[(((unsigned int)&((ENDPOINT_MATRIX*)0)->rows[3])==48)?1:-1];

typedef char actual_scale_method_slot[(sizeof(VENTRY)*3==0x18)?1:-1];
