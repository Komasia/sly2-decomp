typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
union U {qword q;float f[4];};
struct M4 {U rows[4];};
struct FRAME {M4 matrix,world;};
struct VENTRY {short delta,pad;void (*fn)();};
struct OBJECT {char pad0[0xC];VENTRY *vt;};
struct PATH {char pad0[0xC];VENTRY *vt;char pad10[0xD8];int count;int unknownEC;float *distances;U *points;};
struct PARAMS {float fraction,speed,duration;int mode;};
struct SEGMENT {union {float start;int startWord;};union {float speed;int speedWord;};float acceleration,duration;union {float elapsed;int elapsedWord;};};
union TRACKDATA {PARAMS params;struct {int count;SEGMENT segments[6];int current;} motion;};
struct TRACK {PATH *path;float cursor;TRACKDATA data;};
union PAYLOAD {U point;TRACK track;};
struct ENDPOINT {int id,kind;char pad8[8];PAYLOAD payload;};
struct ENTRY {ENDPOINT endpoints[2];char pad140[0x10];};
struct GEOMETRY {int count;U *positions;int normalCount;void *normals;int unknown10,unknown14;};
struct P;
struct BOUND {FRAME *space;P *owner;int unused8,id;ulong flags;char pad18[0x60];GEOMETRY geometry,copy;char padA8[8];};
struct P {char pad0[0xC];VENTRY *vt;char pad10[8];int id;char pad1C[0xC];ulong low:60;ulong attached:1;ulong high:3;char pad30[0x10];unsigned int dirty;char pad44[0x1C];FRAME *space;char pad64[0x7C];int boundCount;BOUND *bounds;char padE8[0xB0];int count;ENTRY *entries;};
struct GAME {char pad0[1];};
struct REQUEST {int size,alignment;};
union WORK {struct {PARAMS params;float rampDistance,lastRampStart;} curve;REQUEST request;};
extern GAME D_003DD490;
extern const qword D_002A2DF0,D_002A2E00;
extern float D_002C3610;
extern "C" {
void func_001F2BA8(P *);
OBJECT *func_0015E938(GAME *,int,int,P *);
int func_00132B10(OBJECT *,int);
float func_001E6648(PATH *);
void func_001E6F10(PATH *,qword *,qword *,float);
void *func_002333B4(void *,int,unsigned int);
qword func_001A62E8(OBJECT *);
qword func_0022FC48(FRAME *,FRAME *,qword);
void *func_001AE2A0(REQUEST *);
void func_00166270(GEOMETRY *,M4 *,GEOMETRY *);
void func_001F2B20(P *);
}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Clamp(float f,float low,float high){if(f<low)return low;else if(high<f)return high;else return f;}
static inline qword Minimum(qword a,qword b){qword r=a;__asm__("vmini.xyz %0,%0,%1":"+j"(r):"j"(b));return r;}
static inline qword Maximum(qword a,qword b){qword r=a;__asm__("vmax.xyz %0,%0,%1":"+j"(r):"j"(b));return r;}
static inline qword Point(const M4 &m,qword a){qword r=a;__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(m.rows[3].q));return r;}
static inline M4 *GetMatrix(PATH *p){VENTRY &e=p->vt[31];return ((M4 *(*)(void *))e.fn)((char *)p+e.delta);}
static inline void MarkDirty(P *p){if(!(p->dirty&1))*(unsigned int *)p->dirty|=2;else p->dirty|=2;}
static inline float Read(const float &value){float r;__asm__("lwc1 %0,%1":"=f"(r):"m"(value));return r;}
static inline void CopyMatrixSnapshot(M4&destination,const M4*source,qword&first,qword&second,qword&third,qword&fourth){
 register qword a __asm__("$7"),b __asm__("$6"),c __asm__("$4"),d __asm__("$3");
 __asm__("lq %0,%5\n\tsq %0,%4\n\tlq %1,16+%5\n\tsq %1,16+%4\n\tlq %2,32+%5\n\tsq %2,32+%4\n\tlq %3,48+%5\n\tsq %3,48+%4":"=&r"(a),"=&r"(b),"=&r"(c),"=&r"(d),"=m"(destination):"m"(*source));
 first=a;second=b;third=c;fourth=d;
}
static inline PATH*UploadMatrixSnapshot(PATH*path,qword first,qword second,qword third,qword fourth,qword&row0,qword&row1,qword&row2,qword&row3){
 register qword a __asm__("$7")=first,b __asm__("$6")=second,c __asm__("$4")=third,d __asm__("$3")=fourth;
 register qword r0 __asm__("vf5"),r1 __asm__("vf4"),r2 __asm__("vf3"),r3 __asm__("vf2");register PATH*loopPath __asm__("$6");
 __asm__("qmtc2.ni %6,%1\n\tqmtc2.ni %5,%0\n\tdaddu %4,%9,$zero\n\tqmtc2.ni %7,%2\n\tqmtc2.ni %8,%3":"=j"(r0),"=j"(r1),"=j"(r2),"=j"(r3),"=r"(loopPath):"r"(a),"r"(b),"r"(c),"r"(d),"r"(path));
 row0=r0;row1=r1;row2=r2;row3=r3;return loopPath;
}
static inline qword PointSnapshot(qword row0,qword row1,qword row2,qword row3,qword point){
 __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(point):"j"(row0),"j"(row1),"j"(row2),"j"(row3));return point;
}
extern "C" void func_001DE5D8(P *p)
{
    WORK work;
    M4 matrix;
    U minimum,maximum;
    func_001F2BA8(p);
    int entryCount=p->count;
    minimum.q=D_002A2DF0;
    maximum.q=D_002A2E00;
    for(int i=0;i<entryCount;){
        ENTRY *entry=&p->entries[i];
        int next=i+1;
        for(unsigned int j=0;j<2;){
            ENDPOINT *endpoint=&entry->endpoints[j];
            unsigned int nextEndpoint=j+1;
            endpoint->kind=-1;
            if(endpoint->id!=-1){
                OBJECT *object=func_0015E938(&D_003DD490,1,endpoint->id,p);
                if(object){
                    if(func_00132B10(object,0xA)){
                        PATH *path=(PATH *)object;
                        work.curve.params=endpoint->payload.track.data.params;
                        work.curve.params.fraction=Clamp(Read(work.curve.params.fraction),0.0f,1.0f);
                        int reverse=0;
                        if(Read(work.curve.params.speed)<0.0f){reverse=1;work.curve.params.speed=-Read(work.curve.params.speed);}
                        work.curve.params.duration=Abs(Read(work.curve.params.duration));
                        if(work.curve.params.mode!=8 && work.curve.params.mode!=16 && work.curve.params.mode!=0)work.curve.params.mode=8;
                        float length=func_001E6648(path);
                        if(0.0f<Read(work.curve.params.duration))work.curve.params.speed=length/Read(work.curve.params.duration);
                        else if(0.0f<Read(work.curve.params.speed))work.curve.params.duration=length/Read(work.curve.params.speed);
                        float start=Read(work.curve.params.fraction)*length;
                        if(Read(work.curve.params.speed)==0.0f || Read(work.curve.params.duration)==0.0f){
                            endpoint->kind=0;
                            func_001E6F10(path,&endpoint->payload.point.q,0,start);
                        }else{
                            endpoint->payload.track.path=path;
                            endpoint->kind=1;
                            endpoint->payload.track.cursor=start;
                            SEGMENT *segments=endpoint->payload.track.data.motion.segments;
                            func_002333B4(segments,0,0x78);
                            switch(work.curve.params.mode){
                            case 8:
                                endpoint->payload.track.data.motion.count=1;
                                if(reverse){
                                    segments[0].start=length;
                                    segments[0].speed=-Read(work.curve.params.speed);
                                    register float one __asm__("$f1")=1.0f;
                                    segments[0].elapsed=(one-Read(work.curve.params.fraction))*Read(work.curve.params.duration);
                                }else{
                                    segments[0].speed=Read(work.curve.params.speed);
                                    segments[0].elapsed=Read(work.curve.params.fraction)*Read(work.curve.params.duration);
                                }
                                segments[0].duration=Read(work.curve.params.duration);
                                endpoint->payload.track.data.motion.current=0;
                                break;
                            case 0:
                                endpoint->payload.track.data.motion.count=2;
                                if(reverse){
                                    segments[0].start=length;
                                    segments[0].speed=-Read(work.curve.params.speed);
                                    register float one __asm__("$f1")=1.0f;
                                    segments[0].elapsed=(one-Read(work.curve.params.fraction))*Read(work.curve.params.duration);
                                }else{
                                    segments[0].speed=Read(work.curve.params.speed);
                                    segments[0].elapsed=Read(work.curve.params.fraction)*Read(work.curve.params.duration);
                                }
                                segments[0].duration=Read(work.curve.params.duration);
                                if(reverse)segments[1].startWord=0;else segments[1].start=length;
                                segments[1].elapsedWord=0;
                                segments[1].speedWord=0;
                                endpoint->payload.track.data.motion.current=0;
                                break;
                            case 16:{
                                if(3.0f*D_002C3610<=length)work.curve.rampDistance=D_002C3610;
                                else work.curve.rampDistance=length*0.2f;
                                float ramp=work.curve.rampDistance+work.curve.rampDistance;
                                work.curve.lastRampStart=length-work.curve.rampDistance;
                                float rampTime=ramp*Read(work.curve.params.duration)/(length+ramp);
                                float middleTime=Read(work.curve.params.duration)-(rampTime+rampTime);
                                work.curve.params.speed=(length-ramp)/middleTime;
                                float acceleration=Read(work.curve.params.speed)*Read(work.curve.params.speed)/ramp;
                                endpoint->payload.track.data.motion.count=6;
                                segments[0].duration=rampTime;
                                segments[0].acceleration=acceleration;
                                segments[1].start=work.curve.rampDistance;
                                segments[1].duration=middleTime;
                                segments[1].speed=Read(work.curve.params.speed);
                                segments[2].start=work.curve.lastRampStart;
                                segments[2].duration=rampTime;
                                segments[2].speed=Read(work.curve.params.speed);
                                segments[2].acceleration=-acceleration;
                                segments[3].start=length;
                                segments[3].duration=rampTime;
                                segments[3].acceleration=-acceleration;
                                segments[4].start=work.curve.lastRampStart;
                                segments[4].duration=middleTime;
                                segments[4].speed=-Read(work.curve.params.speed);
                                segments[5].start=work.curve.rampDistance;
                                segments[5].duration=rampTime;
                                segments[5].acceleration=acceleration;
                                segments[5].speed=-Read(work.curve.params.speed);
                                endpoint->payload.track.data.motion.current=0;
                                for(int n=0;n<3;n++){
                                    SEGMENT *segment=&segments[endpoint->payload.track.data.motion.current];
                                    if(start<segment[1].start){
                                        float elapsed=(start-segment->start)+(start-segment->start);
                                        elapsed=elapsed/(segment->speed+segment[1].speed);
                                        if(reverse){
                                            int index=5-endpoint->payload.track.data.motion.current;
                                            endpoint->payload.track.data.motion.current=index;
                                            segments[index].elapsed=segments[index].duration-elapsed;
                                        }else segment->elapsed=elapsed;
                                        break;
                                    }
                                    endpoint->payload.track.data.motion.current++;
                                }
                                break;
                            }
                            }
                            MarkDirty(p);
                        }
                    }else if(func_00132B10(object,3) || func_00132B10(object,0x30)){
                        endpoint->kind=0;
                        endpoint->payload.point.q=func_001A62E8(object);
                    }
                }
            }
            if(endpoint->kind==-1){endpoint->kind=0;endpoint->payload.point.q=func_001A62E8((OBJECT *)p);}
            j=nextEndpoint;
            switch(endpoint->kind){
            case 0:
                minimum.q=Minimum(minimum.q,endpoint->payload.point.q);
                maximum.q=Maximum(maximum.q,endpoint->payload.point.q);
                endpoint->payload.point.q=func_0022FC48(0,p->space,endpoint->payload.point.q);
                break;
            case 1:{
                PATH *path=endpoint->payload.track.path;
                qword first,second,third,fourth;
                CopyMatrixSnapshot(matrix,GetMatrix(path),first,second,third,fourth);
                path=endpoint->payload.track.path;
                if(path->count>0){
                    qword row0,row1,row2,row3;
                    PATH*loopPath=UploadMatrixSnapshot(path,first,second,third,fourth,row0,row1,row2,row3);
                    int k=0;
                    do {
                        qword position=PointSnapshot(row0,row1,row2,row3,loopPath->points[k].q);
                        maximum.q=Maximum(maximum.q,position);
                        minimum.q=Minimum(minimum.q,position);
                        ++k;
                    }while(k<loopPath->count);
                }
                break;
            }
            }
        }
        i=next;
        entryCount=p->count;
    }
    if(p->count){
        p->boundCount=1;
        work.request.size=0xB0;work.request.alignment=16;
        BOUND *bound=(BOUND *)func_001AE2A0(&work.request);
        p->bounds=bound;
        bound->space=p->space;
        bound->owner=p;
        bound->id=p->id;
        bound->flags|=1UL<<48;
        bound->geometry.count=2;
        work.request.size=0x20;work.request.alignment=16;
        bound->geometry.positions=(U *)func_001AE2A0(&work.request);
        func_00166270(&bound->geometry,0,&bound->copy);
        bound->copy.positions[0].q=minimum.q;
        bound->copy.positions[1].q=maximum.q;
        U *out=bound->geometry.positions;
        out[0].q=func_0022FC48(0,p->space,minimum.q);
        out=bound->geometry.positions;
        out[1].q=func_0022FC48(0,p->space,maximum.q);
    }
    if(p->attached)func_001F2B20(p);
}

typedef char guard_0[(((unsigned int)&((P*)0)->vt)==12)?1:-1];
typedef char guard_1[(((unsigned int)&((P*)0)->id)==24)?1:-1];
typedef char guard_2[(((unsigned int)&((P*)0)->dirty)==64)?1:-1];
typedef char guard_3[(((unsigned int)&((P*)0)->space)==96)?1:-1];
typedef char guard_4[(((unsigned int)&((P*)0)->boundCount)==224)?1:-1];
typedef char guard_5[(((unsigned int)&((P*)0)->bounds)==228)?1:-1];
typedef char guard_6[(((unsigned int)&((P*)0)->count)==408)?1:-1];
typedef char guard_7[(((unsigned int)&((P*)0)->entries)==412)?1:-1];
typedef char guard_8[(((unsigned int)&((ENTRY*)0)->endpoints)==0)?1:-1];
typedef char guard_9[(((unsigned int)&((ENDPOINT*)0)->id)==0)?1:-1];
typedef char guard_10[(((unsigned int)&((ENDPOINT*)0)->kind)==4)?1:-1];
typedef char guard_11[(((unsigned int)&((ENDPOINT*)0)->payload)==16)?1:-1];
typedef char guard_12[(((unsigned int)&((ENDPOINT*)0)->payload.track.path)==16)?1:-1];
typedef char guard_13[(((unsigned int)&((ENDPOINT*)0)->payload.track.cursor)==20)?1:-1];
typedef char guard_14[(((unsigned int)&((ENDPOINT*)0)->payload.track.data.params)==24)?1:-1];
typedef char guard_15[(((unsigned int)&((ENDPOINT*)0)->payload.track.data.motion.count)==24)?1:-1];
typedef char guard_16[(((unsigned int)&((ENDPOINT*)0)->payload.track.data.motion.segments)==28)?1:-1];
typedef char guard_17[(((unsigned int)&((ENDPOINT*)0)->payload.track.data.motion.current)==148)?1:-1];
typedef char guard_18[(((unsigned int)&((PARAMS*)0)->speed)==4)?1:-1];
typedef char guard_19[(((unsigned int)&((PARAMS*)0)->duration)==8)?1:-1];
typedef char guard_20[(((unsigned int)&((PARAMS*)0)->mode)==12)?1:-1];
typedef char guard_21[(((unsigned int)&((SEGMENT*)0)->speed)==4)?1:-1];
typedef char guard_22[(((unsigned int)&((SEGMENT*)0)->acceleration)==8)?1:-1];
typedef char guard_23[(((unsigned int)&((SEGMENT*)0)->duration)==12)?1:-1];
typedef char guard_24[(((unsigned int)&((SEGMENT*)0)->elapsed)==16)?1:-1];
typedef char guard_25[(((unsigned int)&((PATH*)0)->vt)==12)?1:-1];
typedef char guard_26[(((unsigned int)&((PATH*)0)->count)==232)?1:-1];
typedef char guard_27[(((unsigned int)&((PATH*)0)->distances)==240)?1:-1];
typedef char guard_28[(((unsigned int)&((PATH*)0)->points)==244)?1:-1];
typedef char guard_29[(((unsigned int)&((BOUND*)0)->space)==0)?1:-1];
typedef char guard_30[(((unsigned int)&((BOUND*)0)->owner)==4)?1:-1];
typedef char guard_31[(((unsigned int)&((BOUND*)0)->id)==12)?1:-1];
typedef char guard_32[(((unsigned int)&((BOUND*)0)->flags)==16)?1:-1];
typedef char guard_33[(((unsigned int)&((BOUND*)0)->geometry)==120)?1:-1];
typedef char guard_34[(((unsigned int)&((BOUND*)0)->geometry.positions)==124)?1:-1];
typedef char guard_35[(((unsigned int)&((BOUND*)0)->copy)==144)?1:-1];
typedef char guard_36[(((unsigned int)&((BOUND*)0)->copy.positions)==148)?1:-1];
typedef char guard_37[(((unsigned int)&((GEOMETRY*)0)->normalCount)==8)?1:-1];
typedef char guard_38[(((unsigned int)&((GEOMETRY*)0)->normals)==12)?1:-1];
typedef char guard_39[(((unsigned int)&((WORK*)0)->curve.params)==0)?1:-1];
typedef char guard_40[(((unsigned int)&((WORK*)0)->curve.rampDistance)==16)?1:-1];
typedef char guard_41[(((unsigned int)&((WORK*)0)->curve.lastRampStart)==20)?1:-1];
typedef char guard_42[(((unsigned int)&((WORK*)0)->request)==0)?1:-1];
typedef char guard_43[(((unsigned int)&((REQUEST*)0)->alignment)==4)?1:-1];
typedef char guard_44[(sizeof(U)==16)?1:-1];
typedef char guard_45[(sizeof(M4)==64)?1:-1];
typedef char guard_46[(sizeof(FRAME)==128)?1:-1];
typedef char guard_47[(sizeof(PARAMS)==16)?1:-1];
typedef char guard_48[(sizeof(SEGMENT)==20)?1:-1];
typedef char guard_49[(sizeof(TRACKDATA)==128)?1:-1];
typedef char guard_50[(sizeof(TRACK)==136)?1:-1];
typedef char guard_51[(sizeof(PAYLOAD)==144)?1:-1];
typedef char guard_52[(sizeof(ENDPOINT)==160)?1:-1];
typedef char guard_53[(sizeof(ENTRY)==336)?1:-1];
typedef char guard_54[(sizeof(GEOMETRY)==24)?1:-1];
typedef char guard_55[(sizeof(BOUND)==176)?1:-1];
typedef char guard_56[(sizeof(WORK)==24)?1:-1];
typedef char guard_57[(sizeof(REQUEST)==8)?1:-1];
typedef char guard_58[(sizeof(P)==416)?1:-1];
typedef char guard_59[(sizeof(VENTRY)==8)?1:-1];
typedef char guard_60[(sizeof(int)==4)?1:-1];
typedef char guard_61[(((unsigned int)&((SEGMENT*)0)->startWord)==0)?1:-1];
typedef char guard_62[(((unsigned int)&((SEGMENT*)0)->speedWord)==4)?1:-1];
typedef char guard_63[(((unsigned int)&((SEGMENT*)0)->elapsedWord)==16)?1:-1];
typedef char guard_64[(sizeof(ulong)==8)?1:-1];
typedef char guard_65[(sizeof(unsigned int)==4)?1:-1];
typedef char guard_66[(sizeof(void*)==4)?1:-1];
typedef char guard_67[(sizeof(float)==4)?1:-1];
typedef char guard_68[(__alignof__(PAYLOAD)==16)?1:-1];
typedef char guard_69[(sizeof(PATH)==0xF8)?1:-1];
typedef char guard_70[(((unsigned int)&((PARAMS*)0)->fraction)==0)?1:-1];
typedef char guard_71[(sizeof(((ENTRY*)0)->endpoints)==0x140)?1:-1];

typedef char snapshot_matrix_row0[((unsigned)&((M4*)0)->rows[0]==0)?1:-1];
typedef char snapshot_matrix_row1[((unsigned)&((M4*)0)->rows[1]==0x10)?1:-1];
typedef char snapshot_matrix_row2[((unsigned)&((M4*)0)->rows[2]==0x20)?1:-1];
typedef char snapshot_matrix_row3[((unsigned)&((M4*)0)->rows[3]==0x30)?1:-1];
typedef char snapshot_matrix_alignment[(__alignof__(M4)==16)?1:-1];
typedef char snapshot_qword_size[(sizeof(qword)==16)?1:-1];
