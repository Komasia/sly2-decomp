typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
union V {qword q;float f[4];};
struct M4 {qword rows[4];};
struct O {char pad[0x70];qword position;};
struct GEO {int count;qword *points;int planeCount;void *planes;int edgeCount;void *edges;};
struct E {O *object;void *owner;float radius;int tag;ulong flags;int id,initialCount;M4 matrix;E *next;int unused64;char tree[0x10];GEO local,world;int cacheStamp,stamp;};
struct B {qword minimum,maximum,center;float radius;E *first;};
struct P {char pad[0xEC];B *body;};
struct SW {char pad[0x3CCC];int changed;};
extern qword D_002A2DE0,D_002A2DF0,D_002A2E00;
extern SW D_003DD490;
extern "C" {
void func_001F38A8(E *);
void func_001F4BA8(P *);
}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword AddScaled(qword a,qword b,qword scale,V *scalar){scalar->q=scale;__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(scalar->q));return a;}
static inline void Min(qword *a,qword b){__asm__("vmini.xyz %0,%0,%1":"+j"(*a):"j"(b));}
static inline void Max(qword *a,qword b){__asm__("vmax.xyz %0,%0,%1":"+j"(*a):"j"(b));}
static inline void Include(qword *minimum,qword *maximum,qword point){__asm__("vmax.xyz %1,%1,%2\n\tvmini.xyz %0,%0,%2":"+j"(*minimum),"+j"(*maximum):"j"(point));}
static inline qword Transform(const M4 *m,qword point){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(point):"j"(m->rows[0]),"j"(m->rows[1]),"j"(m->rows[2]),"j"(m->rows[3]));return point;}
static inline qword Copy(qword v){qword r;__asm__("vmove.xyzw %0,%1":"=j"(r):"j"(v));return r;}
static inline float Distance(qword center,qword point){qword one;float result;__asm__("vsub.xyzw %0,%1,%0":"+j"(point):"j"(center));__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(point),"=&j"(one));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(point));__asm__("mtc1 %1,%0":"=f"(result):"r"(point));return result;}
static inline ulong Mask50(E *e){register ulong mask asm("v1")=1UL<<50;return e->flags&mask;}
static inline ulong Mask49(E *e){register ulong mask asm("v1")=1UL<<49;return e->flags&mask;}
static inline float LocalDistance(qword center,qword point){register qword delta __asm__("vf2"),one __asm__("vf1");float result;__asm__("vsub.xyzw %0,%2,%3\n\tvmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(delta),"=j"(one):"j"(center),"j"(point));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(delta));__asm__("mtc1 %1,%0":"=f"(result):"r"(delta));return result;}
static inline int ReadCount(const E*e){register int result __asm__("$2");__asm__("lw %0,%1":"=r"(result):"m"(e->world.count));return result;}
static inline qword LocalTransform(const M4*m,const qword& input){register qword point __asm__("vf1");__asm__("lqc2 %0,%1\n\tvmulax.xyz ACC,%2,%0x\n\tvmadday.xyz ACC,%3,%0y\n\tvmaddaz.xyz ACC,%4,%0z\n\tvmaddw.xyz %0,%5,$vf0w":"=&j"(point):"m"(input),"j"(m->rows[0]),"j"(m->rows[1]),"j"(m->rows[2]),"j"(m->rows[3]));return point;}
static inline qword PublishMidpoint(qword minimum,qword maximum,qword half,V& scalar,B& body){register qword center __asm__("vf8");__asm__("vmulax.xyzw ACC,%3,%5x\n\tvmaddx.xyzw %0,%4,%5x\n\tsqc2 %4,%1\n\tsqc2 %5,%2":"=&j"(center),"=m"(body.maximum),"=m"(scalar.q):"j"(minimum),"j"(maximum),"j"(half));return center;}
static inline int HasAppended(int start,int count){register int fits __asm__("$2")=count;__asm__("slt %0,%1,%0":"+r"(fits):"r"(start));return fits;}
extern "C" void func_001F50E0(P *p)
{
    V scalar;
    qword minimum=D_002A2DF0,maximum=D_002A2E00;
    E *e=p->body->first;
    while(e){
        if(!Mask50(e)){
            func_001F38A8(e);
            if(Mask49(e)){
                O *object=e->object;
                float r=e->radius;
                qword positive=Scalar(r);
                qword negative=Scalar(-r);
                qword lo=AddScaled(object->position,D_002A2DE0,negative,&scalar);
                Min(&minimum,lo);
                qword hi=AddScaled(object->position,D_002A2DE0,positive,&scalar);
                Max(&maximum,hi);
            }else{
                int count=ReadCount(e);register int total asm("a2")=count;
                if(count>0){register int remaining asm("a1")=total;register qword *point asm("v0")=e->world.points;do{Include(&minimum,&maximum,*point);++point;}while(--remaining);}
            }
            if(e->cacheStamp!=e->stamp){
                int count=ReadCount(e);register int total asm("a2")=count;register int start asm("a1")=e->initialCount;
                if(HasAppended(start,count)){register qword*point asm("v1")=e->local.points+start;register int remaining asm("a1")=total-start;do{
                    qword position=Transform(&e->matrix,*point);
                    Include(&minimum,&maximum,position);++point;
                }while(--remaining);}
            }
        }
        e=e->next;
    }
    p->body->minimum=minimum;
    qword half=Scalar(0.5f);
    float radius=0.0f;
    register qword center asm("vf8")=PublishMidpoint(minimum,maximum,half,scalar,*p->body);
    e=p->body->first;
    qword sphereCenter=Copy(center);
    if(e){register ulong sphereMask asm("t0")=1UL<<49;
    do{
        if(e->flags&sphereMask){
            float distance=Distance(sphereCenter,e->object->position)+e->radius;
            if(radius<distance)radius=distance;
        }else{
            int count=e->world.count;register int total asm("a2")=count;
            if(count>0){qword copiedCenter=Copy(center);register qword*point asm("v0")=e->world.points;register int remaining asm("a1")=total;do{float distance=Distance(copiedCenter,*point);if(radius<distance)radius=distance;++point;}while(--remaining);}
        }
        if(e->cacheStamp!=e->stamp){
            int count=ReadCount(e);register int total asm("a2")=count;
            register int start asm("a1")=e->initialCount;
            if(HasAppended(start,count)){qword copiedCenter=Copy(center);register qword*point asm("v1")=e->local.points+start;register int remaining asm("a1")=total-start;do{qword position=LocalTransform(&e->matrix,*point);float distance=LocalDistance(copiedCenter,position);if(radius<distance)radius=distance;++point;}while(--remaining);}
        }
        e=e->next;
    }while(e);}
    p->body->center=center;
    p->body->radius=radius;
    D_003DD490.changed=1;
    func_001F4BA8(p);
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_long[(sizeof(ulong)==8)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_vector[(sizeof(V)==16)?1:-1];
typedef char layout_matrix[(sizeof(M4)==0x40)?1:-1];
typedef char layout_object_position[((unsigned)&((O*)0)->position==0x70)?1:-1];
typedef char layout_mesh_size[(sizeof(E)==0xB0)?1:-1];
typedef char layout_mesh_object[((unsigned)&((E*)0)->object==0)?1:-1];
typedef char layout_mesh_radius[((unsigned)&((E*)0)->radius==8)?1:-1];
typedef char layout_mesh_flags[((unsigned)&((E*)0)->flags==0x10)?1:-1];
typedef char layout_mesh_initial_count[((unsigned)&((E*)0)->initialCount==0x1C)?1:-1];
typedef char layout_mesh_matrix[((unsigned)&((E*)0)->matrix==0x20)?1:-1];
typedef char layout_mesh_next[((unsigned)&((E*)0)->next==0x60)?1:-1];
typedef char layout_mesh_tree[((unsigned)&((E*)0)->tree==0x68)?1:-1];
typedef char layout_mesh_local[((unsigned)&((E*)0)->local==0x78)?1:-1];
typedef char layout_mesh_world[((unsigned)&((E*)0)->world==0x90)?1:-1];
typedef char layout_mesh_cache_stamp[((unsigned)&((E*)0)->cacheStamp==0xA8)?1:-1];
typedef char layout_mesh_stamp[((unsigned)&((E*)0)->stamp==0xAC)?1:-1];
typedef char layout_geometry[(sizeof(GEO)==0x18)?1:-1];
typedef char layout_geometry_count[((unsigned)&((GEO*)0)->count==0)?1:-1];
typedef char layout_geometry_points[((unsigned)&((GEO*)0)->points==4)?1:-1];
typedef char layout_minimum[((unsigned)&((B*)0)->minimum==0)?1:-1];
typedef char layout_maximum[((unsigned)&((B*)0)->maximum==0x10)?1:-1];
typedef char layout_center[((unsigned)&((B*)0)->center==0x20)?1:-1];
typedef char layout_radius[((unsigned)&((B*)0)->radius==0x30)?1:-1];
typedef char layout_first_mesh[((unsigned)&((B*)0)->first==0x34)?1:-1];
typedef char layout_body[((unsigned)&((P*)0)->body==0xEC)?1:-1];
typedef char layout_world_changed[((unsigned)&((SW*)0)->changed==0x3CCC)?1:-1];
