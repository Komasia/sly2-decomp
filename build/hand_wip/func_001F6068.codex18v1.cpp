typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct P;
struct VT {short delta,unused;void *function;};
struct MSG {int bytes,alignment;};
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
    {MSG *allocation=&request;
    request.bytes=p->attributeCount*sizeof(ATTR);allocation->alignment=16;
    p->attributes=(ATTR *)func_001AE238(allocation,p->attributes);
    for(;i<p->attributeCount;i++){
        ATTR *attribute=&p->attributes[i];
        Relocate(p,source,&attribute->reference);
        switch(attribute->kind){
        case 4:
            Relocate(p,source,&attribute->payload);
            break;
        case 13:{
            request.bytes=0xE0;allocation->alignment=16;
            CLUMP *clump=(CLUMP *)func_001AE238(allocation,attribute->payload);
            Relocate(p,source,&clump->root);
            Relocate(p,source,&clump->first);
            Relocate(p,source,&clump->second);
            Relocate(p,source,&clump->last);
            clump->first->clump=clump;
            clump->second->clump=clump;
            break;}
        case 15:{
            request.bytes=sizeof(SMALL);allocation->alignment=16;
            SMALL *item=(SMALL *)func_001AE238(allocation,attribute->payload);
            attribute->payload=item;
            if(item->first!=(OBJ *)D_002C44F0)Relocate(p,source,&item->first);
            Relocate(p,source,&item->second);
            break;}
        case 16:{
            CLUMP *clump=(CLUMP *)attribute->payload;
            GROUP *group=clump->group;
            if(group->clumps==clump){
                request.bytes=sizeof(GROUP);allocation->alignment=16;
                group=(GROUP *)func_001AE238(allocation,group);
                request.bytes=group->count*sizeof(CLUMP);allocation->alignment=16;
                group->clumps=(CLUMP *)func_001AE238(allocation,group->clumps);
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
            request.bytes=count*4;allocation->alignment=16;
            PROP **properties=(PROP **)func_001AE318(allocation);
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
    request.bytes=(p->meshCount+Extra(p))*sizeof(E);request.alignment=16;
    p->meshes=(E *)func_001AE238(&request,p->meshes);
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
            request.bytes=sizeof(MESH);request.alignment=16;
            mesh->flags.fields.mesh=(MESH *)func_001AE238(&request,metadata);
            qword *velocity=mesh->flags.fields.mesh->velocity;
            request.bytes=mesh->local.count*16;request.alignment=16;
            mesh->flags.fields.mesh->velocity=(qword *)func_001AE238(&request,velocity);
            qword *acceleration=mesh->flags.fields.mesh->acceleration;
            request.bytes=mesh->local.count*16;request.alignment=16;
            mesh->flags.fields.mesh->acceleration=(qword *)func_001AE238(&request,acceleration);
            void *triangles=mesh->flags.fields.mesh->triangles;
            request.bytes=mesh->local.planeCount*12;request.alignment=16;
            mesh->flags.fields.mesh->triangles=func_001AE238(&request,triangles);
        }
    }
    if(p->dynamic){
        request.bytes=sizeof(STATE);request.alignment=16;
        p->dynamic=(STATE *)func_001AE238(&request,p->dynamic);
        SUB *originalSub=p->dynamic->sub;
        if(originalSub){
            request.bytes=sizeof(SUB);request.alignment=16;
            p->dynamic->sub=(SUB *)func_001AE238(&request,originalSub);
            p->dynamic->sub->owner=p;
        }
    }
    if((int)(p->flags>>60)&1)func_001F2B20(p);
    func_001F2500(p);
}
