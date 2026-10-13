// Insert zeroed vertices, rebuild transformed geometry, and rebase its tree.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {U rows[4];M4(){}M4(const M4&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];}M4&operator=(const M4&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];return *this;}};
struct LO {char pad40[0x40];M4 matrix;};
struct GEO {int count;qword *points;int planeCount;void *planes;int x10,x14;};
struct TREE {int count,flag,unused;void *nodes;};
struct P {LO *owner;int flags;float radius;int material;char pad10[0xC];int pinnedCount;char pad20[0x48];TREE tree;GEO local,world;};
struct FRAME;
extern "C" FRAME *func_001AE478(FRAME *);
extern "C" void func_001AE4A0(FRAME *,int);
struct FRAME {FRAME(){func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
struct MSG {int bytes,alignment;};
extern "C" void *func_001AE378(MSG *);
extern "C" void func_001AE5A0(void *,const void *,unsigned int);
extern "C" M4 func_0011C318(const M4 *);
extern "C" M4 *func_0011C168(M4 *,const M4 *,const M4 *);
extern "C" void func_00166270(GEO *,const M4 *,GEO *);
extern "C" void func_001191E8(TREE *,GEO *,TREE *,GEO *);

static inline float SquaredLength(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Sqrt(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
extern "C" void func_001F70C0(P *source,LO *space,int inserted,P *dest)
{
    M4 transform;
    GEO temporary;
    FRAME frame;
    MSG request;MSG *allocation=&request;
    float maximum=0.0f;
    dest->owner=space;dest->flags=source->flags;dest->material=source->material;dest->pinnedCount=source->pinnedCount;
    {int count=source->local.count;qword *point=source->local.points;
    if(count>0)do{float length=SquaredLength(*point);if(maximum<length)maximum=length;point++;}while(--count);}
    dest->radius=Sqrt(maximum);
    temporary=source->local;
    request.bytes=(temporary.count+inserted)*16;allocation->alignment=16;
    qword *points=(qword *)func_001AE378(allocation);
    int pinned=source->pinnedCount;
    func_001AE5A0(points,temporary.points,pinned*16);
    func_001AE5A0(points+(pinned+inserted),temporary.points+pinned,(temporary.count-pinned)*16);
    temporary.count+=inserted;temporary.points=points;
    {M4 product;M4 inverse=func_0011C318(&space->matrix);func_0011C168(&product,&inverse,&source->owner->matrix);transform=product;}
    func_00166270(&temporary,&transform,&dest->local);
    func_00166270(&dest->local,&space->matrix,&dest->world);
    func_001191E8(&source->tree,&source->world,&dest->tree,&dest->world);
}
