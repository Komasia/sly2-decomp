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
static inline qword AddScaled(qword a,qword b,qword scale,V *scalar){scalar->q=scale;__asm__("vadda.xyzw ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(scalar->q));return a;}
static inline void Min(qword *a,qword b){__asm__("vmini.xyz %0,%0,%1":"+j"(*a):"j"(b));}
static inline void Max(qword *a,qword b){__asm__("vmax.xyz %0,%0,%1":"+j"(*a):"j"(b));}
static inline void Include(qword *minimum,qword *maximum,qword point){__asm__("vmax.xyz %1,%1,%2\n\tvmini.xyz %0,%0,%2":"+j"(*minimum),"+j"(*maximum):"j"(point));}
static inline qword Transform(const M4 *m,qword point){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(point):"j"(m->rows[0]),"j"(m->rows[1]),"j"(m->rows[2]),"j"(m->rows[3]));return point;}
static inline float Distance(qword center,qword point){qword one;float result;__asm__("vsub.xyzw %0,%1,%0":"+j"(point):"j"(center));__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(point),"=&j"(one));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(point));__asm__("qmfc2.ni %0,%1":"=r"(result):"j"(point));return result;}
static inline qword Midpoint(qword a,qword b,qword scale,V *scalar){scalar->q=scale;qword result;__asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x":"=j"(result):"j"(a),"j"(b),"j"(scalar->q));return result;}
extern "C" void func_001F50E0(P *p)
{
    V scalar;
    qword minimum=D_002A2DF0,maximum=D_002A2E00;
    E *e=p->body->first;
    while(e){
        if(!(e->flags&(1UL<<50))){
            func_001F38A8(e);
            if(e->flags&(1UL<<49)){
                float r=e->radius;
                qword positive=Scalar(r);
                qword negative=Scalar(-r);
                qword lo=AddScaled(e->object->position,D_002A2DE0,negative,&scalar);
                Min(&minimum,lo);
                qword hi=AddScaled(e->object->position,D_002A2DE0,positive,&scalar);
                Max(&maximum,hi);
            }else{
                int count=e->world.count;
                for(int i=0;i<count;i++)Include(&minimum,&maximum,e->world.points[i]);
            }
            if(e->cacheStamp!=e->stamp){
                int count=e->world.count;
                for(int i=e->initialCount;i<count;i++){
                    qword position=Transform(&e->matrix,e->local.points[i]);
                    Include(&minimum,&maximum,position);
                }
            }
        }
        e=e->next;
    }
    p->body->minimum=minimum;
    qword half=Scalar(0.5f);
    float radius=0.0f;
    qword center=Midpoint(minimum,maximum,half,&scalar);
    p->body->maximum=maximum;
    e=p->body->first;
    while(e){
        if(e->flags&(1UL<<49)){
            float distance=Distance(center,e->object->position)+e->radius;
            if(radius<distance)radius=distance;
        }else{
            int count=e->world.count;
            for(int i=0;i<count;i++){float distance=Distance(center,e->world.points[i]);if(radius<distance)radius=distance;}
        }
        if(e->cacheStamp!=e->stamp){
            int count=e->world.count;
            for(int i=e->initialCount;i<count;i++){qword position=Transform(&e->matrix,e->local.points[i]);float distance=Distance(center,position);if(radius<distance)radius=distance;}
        }
        e=e->next;
    }
    p->body->center=center;
    p->body->radius=radius;
    D_003DD490.changed=1;
    func_001F4BA8(p);
}
