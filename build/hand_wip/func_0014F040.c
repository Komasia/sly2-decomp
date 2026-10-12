typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct PL { qword pos; qword plane; };
struct P { char pad[0x48]; float g48; };
extern float D_002BD8D8;
extern char D_002BD8E0[];
extern float D_002DDEE0;
void func_002564B8(void *p);
float func_0011D018(float g, float gTarget, float dt, void *pv, float *pr);
static __inline__ float GDistPlane(qword plane, qword pos)
{
    U d, one;
    qword td, tone;
    float dist;
    func_002564B8(&d);
    func_002564B8(&one);
    __asm__("vmul.xyz %0, %3, %4\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %3w\n\tqmfc2.ni %2, %0" : "=j"(td), "=&j"(tone), "=r"(dist) : "j"(plane), "j"(pos));
    one.q = tone;
    d.q = td;
    return dist;
}
static __inline__ float GDot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
float func_0014F040(struct P *p, int unused, qword vIn, struct PL *pl)
{
    float r;
    qword plane = pl->plane;
    qword pos = pl->pos;
    qword v = vIn;
    func_0011D018(GDistPlane(plane, pos), p->g48 - D_002BD8D8, D_002DDEE0, D_002BD8E0, &r);
    return GDot(v, pl->plane) - r;
}
