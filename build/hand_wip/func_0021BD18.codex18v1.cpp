// Complete mesh-history initializer WIP with true copy ABI and embedded model prefix.
typedef int qword __attribute__((mode(TI)));
struct M4 {qword r[4];};
struct Ring {float t,g;M4 m;};
struct QuadBytes {unsigned char b[4];};
struct Sample {qword position;float fraction;QuadBytes extra,color;};
struct Batch {int count;int pad[2];qword *positions;void *uv;QuadBytes *color,*extra;Sample *samples;};
struct Record {char pad[0x14];};
struct Meta {int x0;void *style;char pad8[0x20];};
struct N {Record *record;int count;Batch *batches;N *next;};
struct MODEL {char unknown0[0x3C];Record *records;Meta *metadata;void *output;char unknown48[0x14];N *nodes;};
struct S {char pad[0x40];unsigned int flags;char pad44[0x3C];MODEL model;char padE0[0x70];float fade;int state,count;Ring *ring;int index,idle;float scale;int pad16c;qword axis;};
struct ALLOC {int bytes,align;};
union REQUEST {ALLOC alloc;qword q;float f[4];};
extern "C" {
void func_001F36A8(S *);
void *func_001AE2A0(ALLOC *);
void func_001AE5A0(void *,const void *,unsigned int);
void func_0016EF00(MODEL *,int);
void func_0021BC08(S *);
extern char D_002C44F0[];
extern float D_002A9240,D_002A9244;
}
static inline float Dot(qword a,qword b){qword one;float f;
    __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));
    __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline float DotCopy(qword a,qword b){qword r,one;float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));
    __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
static inline qword Broadcast(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Offset(qword position,qword axis,qword scalar){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(position):"j"(axis),"j"(scalar));return position;}
static inline void RecordOperands(S *owner,N *node,int &bytes,unsigned &divisor,int &stride,Meta *&metadata){
 register Record *rb asm("$4")=owner->model.records;register int span asm("$5");register unsigned d asm("$2");register int st asm("$3");register Meta *mt asm("$6");
 asm("lui %1,0xCCCC\n\tlw %0,%4\n\tori %1,%1,0xCCCD\n\taddiu %2,$zero,40\n\tlw %3,%5\n\tsubu %0,%0,%6":"=&r"(span),"=&r"(d),"=&r"(st),"=&r"(mt):"m"(node->record),"m"(owner->model.metadata),"r"(rb));
 bytes=span;divisor=d;stride=st;metadata=mt;
}
static inline int Product(int value,unsigned scale){int result;asm("mult %0,%1,%2":"=r"(result):"r"(value),"r"(scale):"hi","lo");return result;}
static inline REQUEST *AllocationInput(REQUEST *request){REQUEST *value;__asm__("daddu %0,%1,$zero":"=r"(value):"r"(request));return value;}
static inline qword *BufferStart(qword *buffer){qword *value;__asm__("la %0,%a1":"=r"(value):"p"(buffer));return value;}
static inline Sample *AllocateSamples(REQUEST *request,int count){request->alloc.bytes=count*sizeof(Sample);request->alloc.align=16;return (Sample *)func_001AE2A0(&AllocationInput(request)->alloc);}
extern "C" void func_0021BD18(S *p){
    func_001F36A8(p);
    if(!p->count && p->fade==0.0f)p->fade=0.5f;
    if(p->fade!=0.0f)p->count=(int)(p->fade*60.0f+0.5f)+2;
    else p->fade=(p->count-2)*0.016666668f;
    float minimum,maximum;
    N *node;
    {
        REQUEST req;
        qword buffer[128];
        req.alloc.bytes=p->count*sizeof(Ring);req.alloc.align=16;
        p->ring=(Ring *)func_001AE2A0(&req.alloc);
        minimum=D_002A9240;maximum=D_002A9244;
        for(node=p->model.nodes;node;node=node->next){
            for(int i=0;i<node->count;i++){
                Batch *batch=&node->batches[i];
                func_001AE5A0(buffer,batch->positions,batch->count*16);
                for(int n=batch->count;n>0;){
                    qword *v=BufferStart(buffer);
                    do{float dot=Dot(*v,p->axis);if(maximum<dot)maximum=dot;if(dot<minimum)minimum=dot;v++;}while(--n);
                }
            }
        }
    }
    {
        qword buffer[128];
        REQUEST req;
        for(node=p->model.nodes;node;node=node->next){
            int bytes;unsigned divisor;int stride;Meta *metadata;
            RecordOperands(p,node,bytes,divisor,stride,metadata);
            int index=Product(bytes,divisor)>>2;
            ((Meta *)((char *)metadata+Product(index,stride)))->style=D_002C44F0;
            func_0016EF00(&p->model,index);
            for(int i=0;i<node->count;i++){
                Batch *batch=&node->batches[i];
                func_001AE5A0(buffer,batch->positions,batch->count*16);
                Sample *out=AllocateSamples(&req,batch->count);
                batch->samples=out;
                qword *v=buffer;
                for(int j=0;j<batch->count;j++,v++,out++){
                    qword position=*v,axis=p->axis;
                    float dot=DotCopy(position,axis);
                    float fraction=(dot-minimum)/(maximum-minimum);
                    qword scalar=Broadcast((p->scale-1.0f)*dot);
                    req.q=scalar;
                    out->position=Offset(position,axis,req.q);
                    out->fraction=fraction;
                    if(batch->extra)out->extra=batch->extra[j];
                    if(batch->color)out->color=batch->color[j];
                }
            }
        }
    }
    func_0021BC08(p);
    if(!p->state){unsigned int flags=p->flags;if((flags^1)&1){*(unsigned int *)flags|=2;}else p->flags=flags|2;}
}
