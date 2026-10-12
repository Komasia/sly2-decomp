typedef int qword __attribute__((mode(TI)));
struct LO { char pad[0x28]; int x28; signed char ips; char x2D; long k : 4; unsigned int pad1 : 8; unsigned int f : 1; };
struct Q { char pad[0x50]; int x50; float g54; int x58; };
struct P { char pad[0x14]; struct Q *pq; char pad2[8]; qword v20; };
extern int func_0011D910(void *p, float z);
extern qword func_001A62E8(struct LO *p);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static __inline__ float DistXY(qword d)
{
    qword l;
    float dist;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(l) : "j"(d));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(l));
    return dist;
}
int func_00156FE8(struct LO *plo, struct P *p)
{
    struct Q *pq;
    qword d, l, pos;
    float dist;
    int f;
    if (!plo->f)
        return 0;
    pq = p->pq;
    if (pq->x50)
        return 0;
    pos = func_001A62E8(plo);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(p->v20));
    return func_0011D910(&pq->x58, GetZ(d)) && DistXY(d) < pq->g54;
}
