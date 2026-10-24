extern "C" {
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef union U{qword q;float f[4];}U;
struct M3{U r[3];};
struct M4{U r[4];};
struct V3{float f[3];};
struct SPHERE{struct V3 center;float radius;};
struct D{char pad[8];void*chain;char padC[8];};
struct T{char pad[0x40];struct M4 matrix;};
struct E{int unknown;struct T*transform;struct M4*parent;uint flags;char*matrixData;int word;char pad18[0xC];struct SPHERE*sphere;};
struct LOCAL_SPHERE{struct SPHERE sphere;char pad[8];};
struct P{char pad[0x38];int count;struct D*descriptors;struct E*entries;struct LOCAL_SPHERE*spheres;int pad48;int tick;};
struct PACKET{int word;int reserved[3];U sphere;struct M4 matrix;};
struct R{char pad[0xC];unsigned char*cur;};
struct Q{int kind,pad4;unsigned char*address;void*chain;};
struct G{char pad[0x3D5C];int tick;};
extern struct R D_002DEA28;
extern struct G D_003DD490;
void func_001AE5A0(void*,const void*,uint);
void*func_0023320C(void*,const void*,uint);
struct M4*func_0011C168(struct M4*,const struct M4*,const struct M4*);
float func_0011CAB0(const struct M3*);
struct Q*func_001CD998(void);
static inline qword Transform(const struct M4*m,qword source){
    qword v=source;
    qword row0;
    __asm__("lqc2 %0,%2\n\tlqc2 $vf4,%3\n\tlqc2 $vf3,%4\n\tlqc2 $vf1,%5\n\tvmulax.xyz $ACC,%0,%1x\n\tvmadday.xyz $ACC,$vf4,%1y\n\tvmaddaz.xyz $ACC,$vf3,%1z\n\tvmaddw.xyz %0,$vf1,$vf0w":"=&j"(row0):"j"(v),"m"(m->r[0]),"m"(m->r[1]),"m"(m->r[2]),"m"(m->r[3]):"vf1","vf3","vf4");return row0;
}
static inline void Word(struct R*r,uint value){*(uint*)r->cur=value;r->cur+=4;}
static inline void CopyWords(int*dst,const int*src,int count){int remaining=count-4;do{int a=src[0],b=src[1],c=src[2],d=src[3];src+=4;dst[0]=a;dst[1]=b;dst[2]=c;dst[3]=d;dst+=4;remaining-=4;}while(remaining>=0);}
static inline void Unpack(struct R*r,const void*src,int words,int addr){*(uint*)r->cur=0x6C000000|((words/4)<<16)|0xC000|addr;r->cur+=4;CopyWords((int*)r->cur,(const int*)src,words);r->cur+=words*4;}
static inline void Align(struct R*r){while((uint)r->cur&15){*(uint*)r->cur=0;r->cur+=4;}}
static inline M4 ModelMatrix(const E *entry) return model;{
 const M4 *parent=entry->parent;
 func_0023320C(&model,&entry->transform->matrix,0x40);
 if(parent){M4 product;func_0011C168(&product,&model,parent);func_0023320C(&model,&product,0x40);}
}
static inline void CopyMatrix(struct M4*d,const struct M4*s){(void)func_0023320C(d,s,0x40);}
void func_001681F8(struct P*p){
    int i;
    for(i=0;i<p->count;i++){
        struct D*descriptor=&p->descriptors[i];
        struct E*entry=&p->entries[i];
        struct PACKET packet;
        unsigned char*tag;
        struct Q*q;
        if(!descriptor->chain)continue;
        packet.word=entry->word;
        if(entry->flags&0x1000)func_001AE5A0(&packet.matrix,entry->matrixData+0x14,0x40);
        else packet.matrix=ModelMatrix(entry);
        if(entry->sphere){
            *(struct V3*)&packet.sphere=entry->sphere->center;
            packet.sphere.f[3]=entry->sphere->radius;
        }else{
            int sphereStride=sizeof(LOCAL_SPHERE);
            struct LOCAL_SPHERE*sphere=(LOCAL_SPHERE*)((char*)p->spheres+i*sphereStride);
            U center;
            func_001AE5A0(&center,&sphere->sphere.center,0xC);
            packet.sphere.q=Transform(&packet.matrix,center.q);
            packet.sphere.f[3]=func_0011CAB0((const struct M3*)&packet.matrix)*sphere->sphere.radius;
        }
        tag=D_002DEA28.cur;
        *(ulong*)tag=0x10000000UL;D_002DEA28.cur+=16;
        Unpack(&D_002DEA28,&packet,24,0x301);
        Align(&D_002DEA28);
        *(uint*)tag|=((D_002DEA28.cur-tag)>>4)-1;
        *(ulong*)D_002DEA28.cur=0x60000000UL;D_002DEA28.cur+=16;
        q=func_001CD998();
        q->address=tag;q->kind=0;q->pad4=0;q->chain=descriptor->chain;
    }
    p->tick=D_003DD490.tick;
}

}
