typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x58]; int x; };
struct P { char pad[0x14]; struct Q *pq; char pad2[8]; qword v20; };
extern int func_0011D910(void *p, float z);
extern float SRadiusNoise__FP5NOISE(struct P *p);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
// name: SafeHouse port (FNoiseReaches)
int FNoiseReaches__FP5NOISEG9VU_VECTOR(struct P *p, qword pos)
{
    qword d, l;
    float dist;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(p->v20));
    if (!func_0011D910(&p->pq->x, GetZ(d)))
        return 0;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(l) : "j"(d));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(l));
    { int f = SRadiusNoise__FP5NOISE(p) < dist; return f ^ 1; }
}
