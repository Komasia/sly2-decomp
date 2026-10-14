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
                matrix=*GetMatrix(path);
                // The matrix callback can change the endpoint path.
                path=endpoint->payload.track.path;
                for(int k=0;k<path->count;k++){
                    qword position=Point(matrix,path->points[k].q);
                    maximum.q=Maximum(maximum.q,position);
                    minimum.q=Minimum(minimum.q,position);
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
