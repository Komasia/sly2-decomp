typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
union U {qword q;float f[4];uint words[4];};
struct M4 {U rows[4];};
struct M3 {U rows[3];};
struct VENTRY {short delta,pad;void (*fn)();};
struct OBJECT {char pad0[0xC];VENTRY *vt;};
struct BLOCK;
enum KIND {KIND_INVALID=-1,KIND_MESH=0,KIND_PACKET=1,KIND_DEFERRED=3,KIND_GROUP=4};
union META {ulong bits;uint words[2];struct {ulong coefficient:32;KIND kind:4;long channels:8;long sort:6;ulong hidden:1;ulong index:13;} field;};
struct RENDER {U sphere;META meta;void *payload;BLOCK *next;};
struct BLOCK {RENDER entries[4];};
struct STACK {int count;BLOCK *blocks[256];};
struct TRANSFORM {char pad0[0x40];M4 matrix;};
struct SKIN {char pad0[0xC];void *matrices;int count,regular,extra,unused1C;uint destination;};
struct MESH {int unknown;TRANSFORM *transform;M4 *parent;uint flags;void *data;int unknown14,unknown18;SKIN *skin;char pad20[8];};
struct DESCRIPTOR {int unknown;float distance;void *chain;char padC[8];};
struct SCENE {char pad0[0x24];int animationCount;OBJECT **animations;char pad2C[0xC];int meshCount;DESCRIPTOR *descriptors;MESH *meshes;void *bounds;BLOCK *root;int version;float alpha;};
struct CAMERA {char pad0[0x14];int channels;int unused18;union {float coefficient;uint coefficientWord;};char pad20[0x28];float proximityRadius;char pad4C[0x44];U position;M3 basis;};
struct GAME {char pad0[0x3D5C];int version;};
struct BUILDER {char pad0[0xC];unsigned char *current;};
struct QUEUE {int sort;union {float distance;uint distanceWord;};unsigned char *packet;void *data;};
union FLAG {bool value;uint word;};
union WORK {U constants;M4 inverse;};
extern CAMERA D_002DDF40;
extern GAME D_003DD490;
extern BUILDER D_002DEA28;
extern QUEUE D_003B3980[8192];
extern QUEUE *D_003D4A50;
extern "C" {
int func_001EDA20(OBJECT *);
void func_001681F8(SCENE *);
void func_001D57B8(STACK *,BLOCK *);
BLOCK *func_001D57E0(STACK *);
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
M4 *func_0011C318(M4 *,const M4 *);
}
static inline qword Bits(const uint &value){qword r;__asm__("lw %0,%1":"=r"(r):"m"(value));return r;}
static inline qword CPU(qword q){qword r;__asm__("qmfc2 %0,%1":"=r"(r):"j"(q));return r;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Move(qword q){qword r;__asm__("vmove.xyzw %0,%1":"=j"(r):"j"(q));return r;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline void Virtual(OBJECT *p,int slot){VENTRY &e=p->vt[slot];((void (*)(void *))e.fn)((char *)p+e.delta);}
static inline void Word(BUILDER *b,uint value){*(uint *)b->current=value;b->current+=4;}
static inline void Tag(BUILDER *b,ulong value){*(ulong *)b->current=value;b->current+=16;}
static inline void CopyWords(uint *destination,const uint *source,int words){
    int remaining=words-4;
    do{uint a=source[0],b=source[1],c=source[2],d=source[3];source+=4;destination[0]=a;destination[1]=b;destination[2]=c;destination[3]=d;destination+=4;remaining-=4;}while(remaining>=0);
}
static inline void CopyScalar(uint *destination,const uint *source,int words){
    int remaining=words-1;
    do{uint value=*source++;*destination++=value;remaining--;}while(remaining>=0);
}
static inline void Unpack(BUILDER *b,const void *source,int words,uint opcode){Word(b,opcode);CopyWords((uint *)b->current,(const uint *)source,words);b->current+=words*4;}
static inline void Align(BUILDER *b){while((uint)b->current&15){*(uint *)b->current=0;b->current+=4;}}
static inline QUEUE *Allocate(){QUEUE *q=D_003D4A50;if((uint)(q-D_003B3980)>=8192)return 0;D_003D4A50=q+1;return q;}
static inline void SetSort(QUEUE *q,long sort,float alpha){q->sort=sort;if(alpha<1.0f){if(sort==3 || sort==4)q->sort=5;else q->sort=6;}}
static inline void MeshSort(QUEUE*q,const RENDER*render,float alpha){
    q->sort=render->meta.field.sort;
    if(alpha<1.0f){
        META fresh;__asm__ __volatile__("ld %0,%1":"=r"(fresh.bits):"m"(render->meta));
        long sort=fresh.field.sort;
        if(sort==3 || sort==4)q->sort=5;else q->sort=6;
    }
}
static inline M4 Product(const M4 &a,const M4 &b) return result {func_0011C168(&result,&a,&b);}
static inline M4 Inverse(const M4 &m) return result {func_0011C318(&result,&m);}
static inline const M4 *Bone(void *base,int offset,int n){return (const M4 *)((char *)base+offset+n*0x40);}
extern "C" void func_001D5808(STACK *stack,SCENE *scene)
{
    OBJECT *deferred[512];
    FLAG near;
    for(int i=0;i<scene->animationCount;i++){
        OBJECT *animation=scene->animations[i];
        if(func_001EDA20(animation))Virtual(animation,8);
    }
    if(scene->version!=D_003DD490.version)func_001681F8(scene);
    int deferredCount=0;
    func_001D57B8(stack,scene->root);
    int channels=D_002DDF40.channels;
    BLOCK *block;
    while((block=func_001D57E0(stack))!=0){
        for(unsigned int i=0;i<4;i++){
            register RENDER *render __asm__("s4")=&block->entries[i];
            if(render->meta.field.kind==KIND_INVALID)continue;
            {
                U upload;
                qword coefficient=Bits(D_002DDF40.coefficientWord);
                qword radius=Bits(render->sphere.words[3]);
                __asm__ __volatile__("qmtc2 %0,$vf14" : :"r"(coefficient):"vf14");
                __asm__ __volatile__("sq %1,%0":"=m"(upload.q):"r"(coefficient));
                __asm__ __volatile__("qmtc2 %0,$vf16" : :"r"(radius):"vf16");
                qword metadata=Bits(render->meta.words[0]);
                __asm__ __volatile__("lqc2 $vf15,%0" : :"m"(render->sphere):"vf15");
                __asm__ __volatile__("sq %1,%0":"=m"(upload.q):"r"(radius));
                __asm__ __volatile__("qmtc2 %0,$vf17" : :"r"(metadata):"vf17");
                __asm__ __volatile__("sq %1,%0":"=m"(upload.q):"r"(metadata));
            }
            __asm__ __volatile__("lqc2 $vf10,%0\n\tlqc2 $vf11,%1\n\tlqc2 $vf12,%2\n\tlqc2 $vf13,%3" : :"m"(D_002DDF40.basis.rows[0]),"m"(D_002DDF40.basis.rows[1]),"m"(D_002DDF40.basis.rows[2]),"m"(D_002DDF40.position):"vf10","vf11","vf12","vf13");
            register qword position __asm__("vf18");
            register qword fade __asm__("vf19");
            __asm__ __volatile__("vcallms 0x1C0":"=j"(position),"=j"(fade) : :"vf1","vf2","vf3","vf4","vf5","vf6","vf7","vf8","vf9","vf10","vf11","vf12","vf13","vf14","vf15","vf16","vf17","vf20","vf21","vf22","vf23","vf24","vf25","vf26","vf27","vf28","vf29","vf30","vf31");
            if(!(render->meta.field.channels&channels))continue;
            __asm__ __volatile__("cfc2.i $zero,$vi0":"+j"(position),"+j"(fade));
            float alpha=X(CPU(fade));
            if(alpha==0.0f)continue;
            qword relative=Move(position);
            switch(render->meta.field.kind){
            case KIND_PACKET:{
                if(render->meta.field.hidden)break;
                register QUEUE *q __asm__("s6")=Allocate();if(!q)break;
                SetSort(q,render->meta.field.sort,alpha);
                q->distanceWord=(uint)CPU(Dot(relative,relative));
                if(1.0f<=alpha){q->packet=(unsigned char *)render->payload;q->data=0;}
                else{
                    BUILDER *builder=&D_002DEA28;
                    q->packet=builder->current;
                    q->data=(char *)render->payload+0x70;
                    Tag(builder,0x40000006UL|((ulong)(uint)((char *)render->payload+0x10)<<32));
                    U constants;
                    constants.f[0]=alpha;constants.f[1]=1.0f;constants.f[2]=scene->alpha;constants.words[3]=0;
                    Tag(builder,0x10000002UL);
                    Unpack(builder,&constants,4,0x6C01C008);
                    Align(builder);
                    Tag(builder,0x60000000UL);
                }
                break;
            }
            case KIND_GROUP:func_001D57B8(stack,(BLOCK *)render->payload);break;
            case KIND_DEFERRED:if(deferredCount<512)deferred[deferredCount++]=(OBJECT *)render->payload;break;
            case KIND_MESH:{
                int index=render->meta.field.index;
                register MESH *mesh __asm__("s5")=&scene->meshes[index];
                DESCRIPTOR *descriptor=&scene->descriptors[index];
                if(render->meta.field.hidden)break;
                register QUEUE *q __asm__("s6")=Allocate();if(!q)break;
                MeshSort(q,render,alpha);
                if(mesh->flags&0x400)q->distance=descriptor->distance;else q->distance=X(CPU(Dot(relative,relative)));
                BUILDER *builder=&D_002DEA28;
                register unsigned char *tag __asm__("fp")=builder->current;
                Tag(builder,0x10000000UL);
                if(mesh->parent){
                    M4 matrix;matrix=Product(*mesh->parent,mesh->transform->matrix);
                    Unpack(builder,&matrix,16,0x6C04C000);
                }else Unpack(builder,&mesh->transform->matrix,16,0x6C04C000);
                SKIN *skin=mesh->skin;
                if(skin){
                    M4 inverse;
                    if(mesh->parent){
                        inverse=Inverse(Product(*mesh->parent,mesh->transform->matrix));
                    }else inverse=Inverse(mesh->transform->matrix);
                    uint destination=skin->destination;
                    for(int j=0;j<skin->count;j++){
                        if(skin->regular){
                            M4 matrix;matrix=Product(inverse,*Bone(skin->matrices,0x6F0,j));
                            Unpack(builder,&matrix,16,0x6C04C000|destination);
                            destination+=4;
                        }
                        if(skin->extra){
                            Unpack(builder,Bone(skin->matrices,0x7F0,j),16,0x6C04C000|destination);
                            destination+=4;
                        }
                    }
                }
                U constants;
                constants.f[0]=alpha;constants.f[1]=1.0f;constants.f[2]=scene->alpha;constants.words[3]=0;
                Unpack(builder,&constants,4,0x6C01C008);
                long sort=render->meta.field.sort;
                if(sort==7 || sort==8){
                    float radius=render->sphere.f[3]+D_002DDF40.proximityRadius;
                    near.value=X(CPU(Dot(relative,relative)))<radius*radius;
                    Word(builder,0x6001C012);
                    CopyScalar((uint *)builder->current,&near.word,1);
                    builder->current+=4;
                }
                Align(builder);
                *(uint *)tag|=((builder->current-tag)>>4)-1;
                Tag(builder,0x60000000UL);
                q->packet=tag;
                q->data=mesh->data;
                break;
            }
            }
        }
        if(block->entries[3].next)func_001D57B8(stack,block->entries[3].next);
    }
    for(int i=0;i<deferredCount;i++)Virtual(deferred[i],19);
}

#define OFF(T,M) ((unsigned int)&((T*)0)->M)
typedef char renderer_fact_0[(((unsigned int)&((OBJECT*)0)->vt)==12)?1:-1];
typedef char renderer_fact_1[(((unsigned int)&((RENDER*)0)->sphere)==0)?1:-1];
typedef char renderer_fact_2[(((unsigned int)&((RENDER*)0)->meta)==16)?1:-1];
typedef char renderer_fact_3[(((unsigned int)&((RENDER*)0)->payload)==24)?1:-1];
typedef char renderer_fact_4[(((unsigned int)&((RENDER*)0)->next)==28)?1:-1];
typedef char renderer_fact_5[(((unsigned int)&((STACK*)0)->blocks)==4)?1:-1];
typedef char renderer_fact_6[(((unsigned int)&((TRANSFORM*)0)->matrix)==64)?1:-1];
typedef char renderer_fact_7[(((unsigned int)&((SKIN*)0)->matrices)==12)?1:-1];
typedef char renderer_fact_8[(((unsigned int)&((SKIN*)0)->count)==16)?1:-1];
typedef char renderer_fact_9[(((unsigned int)&((SKIN*)0)->regular)==20)?1:-1];
typedef char renderer_fact_10[(((unsigned int)&((SKIN*)0)->extra)==24)?1:-1];
typedef char renderer_fact_11[(((unsigned int)&((SKIN*)0)->destination)==32)?1:-1];
typedef char renderer_fact_12[(((unsigned int)&((MESH*)0)->transform)==4)?1:-1];
typedef char renderer_fact_13[(((unsigned int)&((MESH*)0)->parent)==8)?1:-1];
typedef char renderer_fact_14[(((unsigned int)&((MESH*)0)->flags)==12)?1:-1];
typedef char renderer_fact_15[(((unsigned int)&((MESH*)0)->data)==16)?1:-1];
typedef char renderer_fact_16[(((unsigned int)&((MESH*)0)->skin)==28)?1:-1];
typedef char renderer_fact_17[(((unsigned int)&((DESCRIPTOR*)0)->distance)==4)?1:-1];
typedef char renderer_fact_18[(((unsigned int)&((DESCRIPTOR*)0)->chain)==8)?1:-1];
typedef char renderer_fact_19[(((unsigned int)&((SCENE*)0)->animationCount)==36)?1:-1];
typedef char renderer_fact_20[(((unsigned int)&((SCENE*)0)->animations)==40)?1:-1];
typedef char renderer_fact_21[(((unsigned int)&((SCENE*)0)->meshCount)==56)?1:-1];
typedef char renderer_fact_22[(((unsigned int)&((SCENE*)0)->descriptors)==60)?1:-1];
typedef char renderer_fact_23[(((unsigned int)&((SCENE*)0)->meshes)==64)?1:-1];
typedef char renderer_fact_24[(((unsigned int)&((SCENE*)0)->root)==72)?1:-1];
typedef char renderer_fact_25[(((unsigned int)&((SCENE*)0)->version)==76)?1:-1];
typedef char renderer_fact_26[(((unsigned int)&((SCENE*)0)->alpha)==80)?1:-1];
typedef char renderer_fact_27[(((unsigned int)&((CAMERA*)0)->channels)==20)?1:-1];
typedef char renderer_fact_28[(((unsigned int)&((CAMERA*)0)->coefficient)==28)?1:-1];
typedef char renderer_fact_29[(((unsigned int)&((CAMERA*)0)->proximityRadius)==72)?1:-1];
typedef char renderer_fact_30[(((unsigned int)&((CAMERA*)0)->position)==144)?1:-1];
typedef char renderer_fact_31[(((unsigned int)&((CAMERA*)0)->basis)==160)?1:-1];
typedef char renderer_fact_32[(((unsigned int)&((GAME*)0)->version)==15708)?1:-1];
typedef char renderer_fact_33[(((unsigned int)&((BUILDER*)0)->current)==12)?1:-1];
typedef char renderer_fact_34[(((unsigned int)&((QUEUE*)0)->distance)==4)?1:-1];
typedef char renderer_fact_35[(((unsigned int)&((QUEUE*)0)->packet)==8)?1:-1];
typedef char renderer_fact_36[(((unsigned int)&((QUEUE*)0)->data)==12)?1:-1];
typedef char renderer_fact_37[(((unsigned int)&((WORK*)0)->constants)==0)?1:-1];
typedef char renderer_fact_38[(((unsigned int)&((WORK*)0)->inverse)==0)?1:-1];
typedef char renderer_fact_39[(sizeof(U)==16)?1:-1];
typedef char renderer_fact_40[(sizeof(M4)==64)?1:-1];
typedef char renderer_fact_41[(sizeof(M3)==48)?1:-1];
typedef char renderer_fact_42[(sizeof(META)==8)?1:-1];
typedef char renderer_fact_43[(sizeof(RENDER)==32)?1:-1];
typedef char renderer_fact_44[(sizeof(BLOCK)==128)?1:-1];
typedef char renderer_fact_45[(sizeof(STACK)==1028)?1:-1];
typedef char renderer_fact_46[(sizeof(MESH)==40)?1:-1];
typedef char renderer_fact_47[(sizeof(DESCRIPTOR)==20)?1:-1];
typedef char renderer_fact_48[(sizeof(QUEUE)==16)?1:-1];
typedef char renderer_fact_49[(sizeof(WORK)==64)?1:-1];
typedef char renderer_fact_50[(sizeof(VENTRY)==8)?1:-1];
typedef char renderer_fact_51[(sizeof(uint)==4)?1:-1];
typedef char renderer_fact_52[(((unsigned int)&((META*)0)->words)==0)?1:-1];
typedef char renderer_fact_53[(sizeof(((META*)0)->words)==8)?1:-1];
typedef char renderer_fact_54[(((unsigned int)&((CAMERA*)0)->coefficientWord)==0x1C)?1:-1];
typedef char renderer_fact_55[(((unsigned int)&((QUEUE*)0)->distanceWord)==4)?1:-1];
typedef char renderer_fact_56[(sizeof(KIND)==4)?1:-1];
typedef char renderer_fact_57[(sizeof(FLAG)==4)?1:-1];
typedef char renderer_fact_58[(__alignof__(FLAG)==4)?1:-1];
typedef char renderer_fact_59[(OFF(FLAG,value)==0)?1:-1];
typedef char renderer_fact_60[(OFF(FLAG,word)==0)?1:-1];
typedef char renderer_fact_61[(sizeof(bool)==4)?1:-1];
typedef char renderer_fact_62[(KIND_INVALID==-1)?1:-1];
typedef char renderer_fact_63[(KIND_MESH==0)?1:-1];
typedef char renderer_fact_64[(KIND_PACKET==1)?1:-1];
typedef char renderer_fact_65[(KIND_DEFERRED==3)?1:-1];
typedef char renderer_fact_66[(KIND_GROUP==4)?1:-1];
