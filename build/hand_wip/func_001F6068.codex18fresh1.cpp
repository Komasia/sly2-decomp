typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct P;
struct VT {short delta,unused;void *function;};
struct MSG {int bytes,alignment;void *Copy(int,const void *);void *Allocate(int);};
struct LINKS {int a,b,c;};
struct FRAME {FRAME(){}~FRAME(){}};
struct OBJ {char pad[0xA8];void *clump;};
struct PROP {char pad0[0x10];PROP *next;};
struct GROUP;
struct CLUMP {OBJ *root,*first,*second,*last;char pad10[0x50];GROUP *group;OBJ *object;char pad68[8];};
struct GROUP {int count;CLUMP *clumps;char pad8[0x48];};
struct SMALL {OBJ *first,*second;int a,b;};
struct ATTR {char pad0[0x90];PROP *properties;int unused94;short kind;char pad9A[6];OBJ *reference;int unusedA4;void *payload;char padAC[0x54];};
struct GEO {int count;qword *points;int planeCount;void *planes;int edgeCount;void *edges;};
struct TREE {int count,a,b;void *nodes;};
struct M4 {qword rows[4];};
struct MESH {qword *velocity,*acceleration;void *triangles;};
union FLAGS {ulong raw;struct {MESH *mesh;short state;unsigned short high;} fields;};
struct E {void *object;P *owner;float radius;int tag;FLAGS flags;int id,pinned;M4 matrix;void *next,*previous;TREE tree;GEO local,world;int state,stamp;};
struct SUB {P *owner;char pad4[0x6C];};
struct STATE {qword rows[3];char pad30[0xA0];float mass;char padD4[8];SUB *sub;};
struct DATA {char values[0x60];};
struct P {char pad0[0xC];VT *vtable;char pad10[0x18];ulong flags;char pad30[0x20];int attributeCount;ATTR *attributes;void *references[3];LINKS links;int state;char pad74[0xC];DATA data;int meshCount;E *meshes;STATE *dynamic;void *attachment;char padF0[0x44];void *cache;};
extern char D_002C44F0[];
extern "C" {
void func_001A6730(P *,P *);
void *func_001AE238(MSG *,const void *);
void *func_001AE318(MSG *);
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *,int);
PROP *func_0012E3F0(PROP *,P *,ATTR *);
void func_00230018(P *,ATTR *,PROP *);
void func_0016EA80(DATA *,P *,P *);
void func_0011A210(void *);
void func_00166270(GEO *,const M4 *,GEO *);
void func_001191E8(TREE *,GEO *,TREE *,GEO *);
void func_001F2B20(P *);
void func_001F2500(P *);
}
inline void *MSG::Copy(int n,const void *source)
{
    bytes=n;
    alignment=16;
    return func_001AE238(this,source);
}
inline void *MSG::Allocate(int n)
{
    bytes=n;
    alignment=16;
    return func_001AE318(this);
}
static inline void Relocate(P *p,P *source,void *slot){VT *entry=&p->vtable[52];((void (*)(void *,P *,void *))entry->function)((char *)p+entry->delta,source,slot);}
static inline int Extra(P *p){VT *entry=&p->vtable[63];return ((int (*)(void *))entry->function)((char *)p+entry->delta);}
extern "C" void func_001F6068(P *p,P *source)
{
    void *attachment=p->attachment;
    int state=p->state;
    LINKS links=p->links;
    int i=0;
    func_001A6730(p,source);
    p->attachment=attachment;
    p->links=links;
    p->state=state;
    p->cache=0;
    MSG request;
    {
    p->attributes=(ATTR *)request.Copy(p->attributeCount*sizeof(ATTR),p->attributes);
    for(;i<p->attributeCount;i++){
        ATTR *attribute=&p->attributes[i];
        Relocate(p,source,&attribute->reference);
        switch(attribute->kind){
        case 4:
            Relocate(p,source,&attribute->payload);
            break;
        case 13:{
            CLUMP *clump=(CLUMP *)request.Copy(0xE0,attribute->payload);
            Relocate(p,source,&clump->root);
            Relocate(p,source,&clump->first);
            Relocate(p,source,&clump->second);
            Relocate(p,source,&clump->last);
            clump->first->clump=clump;
            clump->second->clump=clump;
            break;}
        case 15:{
            SMALL *item=(SMALL *)request.Copy(sizeof(SMALL),attribute->payload);
            attribute->payload=item;
            if(item->first!=(OBJ *)D_002C44F0)Relocate(p,source,&item->first);
            Relocate(p,source,&item->second);
            break;}
        case 16:{
            CLUMP *clump=(CLUMP *)attribute->payload;
            GROUP *group=clump->group;
            if(clump==group->clumps){
                group=(GROUP *)request.Copy(sizeof(GROUP),group);
                group->clumps=(CLUMP *)request.Copy(group->count*sizeof(CLUMP),group->clumps);
                for(int groupIndex=0;groupIndex<group->count;groupIndex++){
                    CLUMP *member=&group->clumps[groupIndex];
                    member->group=group;
                    Relocate(p,source,&member->object);
                    member->object->clump=member;
                }
            }
            break;}
        }
        if(attribute->properties){
            int count=0;
            for(PROP *property=attribute->properties;property;property=property->next)count++;
            FRAME storage;
            FRAME *frame=&storage;
            func_001AE478(frame);
            PROP **properties=(PROP **)request.Allocate(count*4);
            PROP **output=properties;
            for(PROP *property=attribute->properties;property;property=property->next)*output++=property;
            attribute->properties=0;
            for(int j=count-1;j>=0;j--){
                PROP *property=func_0012E3F0(properties[j],p,attribute);
                func_00230018(p,attribute,property);
            }
            func_001AE4A0(frame,2);
        }
    }
    }
    int meshIndex=0;
    Relocate(p,source,&p->references[0]);
    Relocate(p,source,&p->references[1]);
    Relocate(p,source,&p->references[2]);
    func_0016EA80(&p->data,p,source);
    p->meshes=(E *)request.Copy((p->meshCount+Extra(p))*sizeof(E),p->meshes);
    for(;meshIndex<p->meshCount;meshIndex++){
        E *mesh=&p->meshes[meshIndex];
        Relocate(p,source,&mesh->object);
        mesh->owner=p;
        func_0011A210(&mesh->next);
        GEO geometry;
        GEO *world=&mesh->world;
        func_00166270(world,0,&geometry);
        *world=geometry;
        E *original=&source->meshes[meshIndex];
        func_001191E8(&original->tree,&original->world,&mesh->tree,world);
        MESH *metadata=mesh->flags.fields.mesh;
        if(metadata){
            mesh->flags.fields.mesh=(MESH *)request.Copy(sizeof(MESH),metadata);
            qword *velocity=mesh->flags.fields.mesh->velocity;
            mesh->flags.fields.mesh->velocity=(qword *)request.Copy(mesh->local.count*16,velocity);
            qword *acceleration=mesh->flags.fields.mesh->acceleration;
            mesh->flags.fields.mesh->acceleration=(qword *)request.Copy(mesh->local.count*16,acceleration);
            void *triangles=mesh->flags.fields.mesh->triangles;
            mesh->flags.fields.mesh->triangles=request.Copy(mesh->local.planeCount*12,triangles);
        }
    }
    if(p->dynamic){
                p->dynamic=(STATE *)request.Copy(sizeof(STATE),p->dynamic);
        SUB *originalSub=p->dynamic->sub;
        if(originalSub){
            p->dynamic->sub=(SUB *)request.Copy(sizeof(SUB),originalSub);
            p->dynamic->sub->owner=p;
        }
    }
    if((int)(p->flags>>60)&1)func_001F2B20(p);
    func_001F2500(p);
}

#define OFF(t,f) ((int)&((t *)0)->f)
typedef char verified_layout[(sizeof(FRAME)==1&&sizeof(MSG)==8&&sizeof(ATTR)==0x100&&sizeof(CLUMP)==0x70&&sizeof(GROUP)==0x50&&sizeof(SMALL)==0x10&&sizeof(E)==0xB0&&sizeof(GEO)==0x18&&sizeof(TREE)==0x10&&sizeof(STATE)==0xE0&&sizeof(SUB)==0x70&&OFF(CLUMP,group)==0x60&&OFF(CLUMP,object)==0x64&&OFF(OBJ,clump)==0xA8&&OFF(PROP,next)==0x10&&OFF(ATTR,properties)==0x90&&OFF(ATTR,kind)==0x98&&OFF(ATTR,reference)==0xA0&&OFF(ATTR,payload)==0xA8&&OFF(E,flags)==0x10&&OFF(E,matrix)==0x20&&OFF(E,next)==0x60&&OFF(E,tree)==0x68&&OFF(E,local)==0x78&&OFF(E,world)==0x90&&OFF(STATE,sub)==0xDC&&OFF(P,vtable)==0xC&&OFF(P,flags)==0x28&&OFF(P,attributeCount)==0x50&&OFF(P,attributes)==0x54&&OFF(P,references)==0x58&&OFF(P,links)==0x64&&OFF(P,state)==0x70&&OFF(P,data)==0x80&&OFF(P,meshCount)==0xE0&&OFF(P,meshes)==0xE4&&OFF(P,dynamic)==0xE8&&OFF(P,attachment)==0xEC&&OFF(P,cache)==0x134)?1:-1];
