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
static inline void CopyMatrix(M4&destination,const M4&source){qword a=source.rows[0].q,b=source.rows[1].q,c=source.rows[2].q,d=source.rows[3].q;destination.rows[0].q=a;destination.rows[1].q=b;destination.rows[2].q=c;destination.rows[3].q=d;}
static inline void CopyBasis(M3&destination,const M3&source){qword a=source.rows[0].q,b=source.rows[1].q,c=source.rows[2].q;destination.rows[0].q=a;destination.rows[1].q=b;destination.rows[2].q=c;}
static inline qword BroadcastInto(float value,U&home){qword result;__asm__("qmtc2.ni %1,%0":"=j"(result):"r"(value));home.q=result;return home.q;}
static inline qword Scalar(const float *p){qword r;__asm__("lw %0,%1":"=r"(r):"m"(*p));return r;}
static inline qword Subtract(qword first,qword second){register qword a __asm__("vf2")=first;register qword b __asm__("vf1")=second;register qword r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(const U&value){register qword a __asm__("vf4")=value.q;register qword d __asm__("vf1");register qword one __asm__("vf2");float r;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));__asm__("mtc1 %1,%0":"=f"(r):"r"(d));return r;}
static inline int ElementOffset(int index){register int stride __asm__("$2")=sizeof(ENTRY);register int offset __asm__("$2");__asm__("mult %0,%1,%2":"=r"(offset):"r"(index),"r"(stride):"hi","lo");return offset;}
static inline void Query(P*owner,ENTRY*entry,U(&points)[2],DISTANCE&distance){func_001DEF98(owner,entry,&points[0].q,&distance.value);}
extern "C" void func_001DF5B0(P *p)
{
    U scalar,points[2];
    M3 basis;
    PHASE workspace;
    MEASUREMENT measurement;
    func_001F3C70(p);
    register BOUND *bound __asm__("$3") = p->bound;
    if(!bound)return;
    scalar.q=Scalar(&bound->radius);
    if(!func_0014F850(&D_002DDF40,Subtract(bound->position.q,D_002DDF40.position.q),scalar.q))return;
    for(int i=0;i<p->count;){
        ENTRY *entry=(ENTRY*)((char*)p->entries+ElementOffset(i));
        Query(p,entry,points,measurement.distance);
        if(entry->maximumLength<measurement.distance.value){
            float ratio=entry->maximumLength/measurement.distance.value;
            points[1].q=Add(Scale(points[0].q,BroadcastInto(1.0f-ratio,scalar)),Scale(points[1].q,BroadcastInto(ratio,scalar)));
        }
        if(p->line)func_001A5FB8(p->line,points[0].q,points[1].q,1.0f,1.0f);
        if(p->stretch||p->endpoints[0].object||p->endpoints[1].object){
            measurement.direction.q=Subtract(points[1].q,points[0].q);
            func_0011B830(&workspace.initial.facing,measurement.direction.q,D_002A2DC0);
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
                M4 &transform=workspace.endpoint.matrix;
                if(end->scale){
                    HOOK *scale=end->scale;
                    VENTRY &callback=scale->vt[3];
                    callback.fn((char *)scale+callback.delta,&scalar,0,end->config->first,end->config->second);
                    func_0011C210(&workspace.endpoint.output,points[j].q,&basis,&scalar);
                    CopyMatrix(transform,workspace.endpoint.output);
                }else{
                    func_00256D18(&transform.rows[3].q,points[j].q);
                    transform.rows[0]=basis.rows[0];
                    transform.rows[1]=basis.rows[1];
                    transform.rows[2]=basis.rows[2];
                    transform.rows[0].bits[3]=transform.rows[1].bits[3]=transform.rows[2].bits[3]=0;
                    transform.rows[3].f[3]=1.0f;
                }
                func_001A5EE8(end->object,&transform,1.0f,1.0f);
            }
        }
        i=next;
    }
}
