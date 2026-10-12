typedef int qword __attribute__((mode(TI)));
typedef struct CLOCK { float t; float dt; } CLOCK;
extern CLOCK D_002DDED0;
typedef struct Q { char pad[0x30]; qword a; char pad2[0x68]; float t; char pad3[4]; qword b; } Q;
typedef struct P { char pad[8]; Q *pq; char pad2[0x14]; qword v20; qword v30; } P;
void func_00117120(qword a, qword b, qword c, qword d, float g, float t, float u, qword *pa, qword *pb, int n);
void func_0012E060(P *p, qword *pa, qword *pb, float t)
{
    float g = D_002DDED0.t;
    Q *pq = p->pq;
    if (pq->t <= g + t) {
        if (pa) *pa = p->v20;
        if (pb) *pb = p->v30;
    } else {
        func_00117120(pq->a, pq->b, p->v20, p->v30, pq->t - g, t, 1.0f, pa, pb, 0);
    }
}
