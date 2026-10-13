typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int bits[4];};
struct M4 {U rows[4];};
struct PLANE {U value;};
struct VENTRY {short delta,pad;void (*fn)();};
struct OWNER {char pad0[0xC];VENTRY *vt;char pad10[0xD4];void *collision;};
struct ENTRY {char pad0[8];void *contacts;char padC[0x14];float radius,minimumHeight,maximumHeight;char pad2C[0x24];U position;};
struct SURFACE;
struct EDGE {unsigned short firstVertex,secondVertex,firstSurface,secondSurface;EDGE *next;};
struct SURFACE {PLANE plane;EDGE *edges;int unknown14,flags,unknown1C;};
struct POLYGON {int kind;void *binding;char pad8[0x8C];U *positions;int unknown98;SURFACE *surfaces;};
struct NODE {NODE *left,*right;SURFACE *surface;};
struct HIT {U start,end,startNormal,endNormal;float startFraction,endFraction;int kind;SURFACE *startSurface,*endSurface;char pad54[0xC];};
struct RECORD {U position;SURFACE *first,*second;int used,unknown1C;};
struct QUERY {int capacity;NODE *next;};
struct REQUEST {int size,alignment;};
union TEMP {M4 inverse;PLANE plane;REQUEST request;struct {U blend,local,scalar;} intersection;struct {PLANE plane;U point,packed;} support;U scalar;};
struct GAME {char unknown[1];};
struct SCALAR;
struct VECTOR;
struct GUARD;
extern GAME D_003DD490;
extern const qword D_002A2DC0,D_002C2150[5];
extern float D_002A7838,D_002A783C;
extern "C" {
qword func_001A6F00(OWNER *,OWNER *,qword);
qword *func_00256D18(qword *,qword);
M4 *func_0011C318(M4 *,const M4 *);
void func_00119390(PLANE *,qword,qword);
void *func_002333B4(void *,int,unsigned int);
GUARD *func_001AE478(GUARD *);
void func_001AE4A0(GUARD *,int);
void *func_001AE318(REQUEST *);
int func_00118A88(NODE *,NODE *,qword,int *,NODE **,float);
SCALAR *func_002564B8(SCALAR *);
VECTOR *func_002564C0(VECTOR *);
int func_00118668(NODE *,NODE *,qword,qword,int,HIT *);
qword func_001193D8(const M4 *,qword);
void func_001A7C18(GAME *,void *,POLYGON *,qword,qword,int,int,int,void *,float);
}
struct GUARD {GUARD(){func_001AE478(this);}~GUARD(){func_001AE4A0(this,2);}};
struct SCALAR {qword q;SCALAR(){func_002564B8(this);}};
struct VECTOR {qword q;VECTOR(){func_002564C0(this);}};
static inline M4 *GetMatrix(OWNER *p){VENTRY &e=p->vt[31];return ((M4 *(*)(void *))e.fn)((char *)p+e.delta);}
static inline float Sqrt(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword VectorValue(qword q){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(q));return r;}
static inline qword ScalarValue(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarCPU(float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));return r;}
static inline qword Pack(float x,float y,float z){qword a,b;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(a),"=&r"(b):"f"(x),"f"(y),"f"(z));return a;}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Combine(qword a,qword x,qword b,qword y){qword r;__asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(a),"j"(x),"j"(b),"j"(y));return r;}
static inline qword Point(const M4 &m,qword a){qword r=a;__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m.rows[0].q),"j"(m.rows[1].q),"j"(m.rows[2].q),"j"(m.rows[3].q));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline float PlaneDistance(qword plane,qword point){
    SCALAR result,one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"=j"(result.q),"=&j"(one.q):"j"(plane),"j"(point));
    return X(result.q);
}
static inline float Clamp(float f,float low,float high){if(f<low)return low;else if(high<f)return high;else return f;}
static inline qword LoadVF(const U &value){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(value));return r;}
static inline qword CPU(qword q){qword r;__asm__("qmfc2 %0,%1":"=r"(r):"j"(q));return r;}
extern "C" void func_001D3450(OWNER *owner,ENTRY *entry,POLYGON *polygon,int unused3,int unused4,NODE *root,void *contactHead)
{
    M4 frame,inverse;
    TEMP temp;
    RECORD records[64];
    int count=0;
    M4 *source=GetMatrix(owner);
    func_00256D18(&frame.rows[3].q,func_001A6F00(owner,0,entry->position.q));
    frame.rows[0]=source->rows[0];frame.rows[1]=source->rows[1];frame.rows[2]=source->rows[2];
    frame.rows[3].f[3]=1.0f;
    frame.rows[2].bits[3]=0;frame.rows[1].bits[3]=0;frame.rows[0].bits[3]=0;
    func_0011C318(&temp.inverse,&frame);
    register float height __asm__("$f27")=entry->maximumHeight-entry->minimumHeight;
    register float radius __asm__("$f22")=entry->radius;
    inverse=temp.inverse;
    func_00119390(&temp.plane,frame.rows[1].q,frame.rows[3].q);
    PLANE plane=temp.plane;
    func_002333B4(records,0,sizeof(records));
    GUARD guard;
    HIT hits[16];
    QUERY query;
    temp.request.size=0xFFFC;temp.request.alignment=16;
    NODE *nodes=(NODE *)func_001AE318(&temp.request);
    query.next=nodes;query.capacity=0x1555;
    if(func_00118A88(root,(NODE *)0x7FFFFFFF,frame.rows[3].q,&query.capacity,&query.next,Sqrt(radius*radius+height*height))!=2)return;
    int nodeCount=query.next-nodes;
    query.next--;
    SURFACE *surfaces=polygon->surfaces;
    U radiusScalar,heightScalar;
    radiusScalar.q=ScalarCPU(radius);heightScalar.q=ScalarCPU(height);
    for(int n=0;n<nodeCount;n++)nodes[n].surface->flags|=0x400;
    for(int n=0;n<nodeCount;){
        int nextNode=n+1;
        SURFACE *surface=nodes[n].surface;
        if(!(surface->flags&0x800)){
            surface->flags|=0x800;
            for(EDGE *edge=surface->edges;edge;edge=edge->next){
                SURFACE *other=&surfaces[edge->firstSurface];
                if(other==surface)other=&surfaces[edge->secondSurface];
                if(!(other->flags&0x400))continue;
                U first,second;
                first.q=polygon->positions[edge->firstVertex].q;
                second.q=polygon->positions[edge->secondVertex].q;
                float firstDistance=PlaneDistance(plane.value.q,first.q);
                float secondDistance=PlaneDistance(plane.value.q,second.q);
                float fraction=firstDistance/(firstDistance-secondDistance);
                if(fraction<0.0f || 1.0f<fraction)continue;
                temp.intersection.scalar.q=ScalarValue(1.0f-fraction);
                qword firstWeight=temp.intersection.scalar.q;
                temp.intersection.scalar.q=ScalarValue(fraction);
                temp.intersection.blend.q=Combine(first.q,firstWeight,second.q,temp.intersection.scalar.q);
                temp.intersection.local.q=Point(inverse,temp.intersection.blend.q);
                if(0.0f<temp.intersection.local.f[2]){
                    if(radius<Abs(temp.intersection.local.f[0]))continue;
                }else if(radius*radius<X(Dot(temp.intersection.local.q,temp.intersection.local.q)))continue;
                VECTOR normal;
                RECORD *record=&records[count++];
                float orientation=X(Dot(plane.value.q,Subtract(first.q,second.q)));
                normal.q=plane.value.q;
                if(orientation<0.0f){record->first=surface;record->second=other;}
                else{record->first=other;record->second=surface;}
                record->position.q=temp.intersection.local.q;
            }
        }
        n=nextNode;
    }
    for(int n=0;n<nodeCount;n++)nodes[n].surface->flags&=~0xC00;
    qword radiusVector=LoadVF(radiusScalar);
    qword heightVector=LoadVF(heightScalar);
    qword center=Point(frame,Combine(D_002C2150[0],radiusVector,D_002A2DC0,heightVector));
    for(unsigned int n=0;n<6;n++){
        qword direction;
        temp.scalar.q=radiusVector;
        if(n<5)direction=Scale(D_002C2150[n],temp.scalar.q);
        else{
            temp.scalar.q=heightVector;
            direction=Combine(D_002C2150[4],radiusVector,D_002A2DC0,temp.scalar.q);
        }
        qword endpoint=Point(frame,direction);
        int hitCount=func_00118668(query.next,(NODE *)0x7FFFFFFF,CPU(center),CPU(endpoint),16,hits);
        for(int j=0;j<hitCount;j++){
            if(hits[j].startSurface){
                RECORD *record=&records[count++];
                record->second=hits[j].startSurface;
                record->position.q=Point(inverse,hits[j].start.q);
            }
            if(hits[j].endSurface){
                RECORD *record=&records[count++];
                record->first=hits[j].endSurface;
                record->position.q=Point(inverse,hits[j].end.q);
            }
        }
    }
    register float correction __asm__("$f23")=0.0f;
    U correctedPoint;
    for(int pass=0;pass<2;pass++){
        register float zero __asm__("$f25")=0.0f;
        for(int n=0;n<count;n++){
            RECORD *record=&records[n];
            register float lower __asm__("$f26");register float upper __asm__("$f24");
            SURFACE *surface;
            if(pass==0){
                surface=record->second;if(!surface)continue;
                if(record->first)lower=record->position.f[0];else lower=D_002A7838;
                upper=D_002A783C;
                RECORD *partner=0;
                for(int k=0;k<count;k++){
                    RECORD *candidate=&records[k];
                    if(candidate->first==surface){
                        float x=candidate->position.f[0];
                        if(lower<x){if(x<upper){upper=x;partner=candidate;}}
                    }
                }
                if(partner)partner->used=1;
            }else{
                surface=record->first;if(!surface || record->used)continue;
                lower=D_002A7838;
                if(record->second)upper=record->position.f[0];else upper=D_002A783C;
            }
            temp.support.plane.value.q=func_001193D8(&inverse,surface->plane.value.q);
            if(temp.support.plane.value.f[2]<0.0f)continue;
            float slope=-temp.support.plane.value.f[0]/temp.support.plane.value.f[2];
            float squaredRadius=radius*radius;
            register float x __asm__("$f20")=Sqrt(squaredRadius*slope*slope/(slope*slope+1.0f));
            if(slope<0.0f)x=-x;
            x=Clamp(x,lower,upper);
            register float z __asm__("$f21")=-Sqrt(squaredRadius-x*x);
            temp.support.point.f[0]=x;temp.support.point.bits[1]=0;temp.support.point.f[2]=z;
            float amount=Min(-PlaneDistance(temp.support.plane.value.q,temp.support.point.q)/temp.support.plane.value.f[2],height);
            if(correction<amount){
                correction=amount;
                temp.support.packed.q=Pack(x,zero,z+correction);
                correctedPoint.q=temp.support.packed.q;
            }
        }
    }
    if(0.0f<correction){
        U worldPoint;
        worldPoint.q=Point(frame,correctedPoint.q);
        VECTOR normal;
        normal.q=plane.value.q;
        func_001A7C18(&D_003DD490,owner->collision,polygon,worldPoint.q,normal.q,0xA,0,0,contactHead,correction);
    }
}
