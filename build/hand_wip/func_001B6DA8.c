typedef int qword __attribute__((mode(TI)));
struct VT { short d; short pad; void *pfn; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern char D_003DD490[];
extern qword D_002A2DC0;
extern float D_002C09A8;
struct SIDE { int x0; int x4; void *x8; void *xC; qword v10; char pad[0x30 - 0x20]; qword v30; };
struct LINK { struct SIDE as[2]; char pad[0xAC - 0x80]; struct LINK *pnext; };
struct MSG { void *x0; int x4; void *x8; int xC; int x10; char pad[0x20 - 0x14]; qword v20; qword v30; char pad2[0x60 - 0x40]; };
struct Q { char pad[0x14]; void *x14; };
struct V3 { float x, y, z; };
struct P {
    char pad0[0xC]; struct VT *vt; char pad1[0x190 - 0x10]; struct V3 v190; char pad2[0x1030 - 0x19C]; struct Q *p1030;
    char pad3[0x131C - 0x1034]; float g131C; char pad4[0x13D8 - 0x1320]; int x13D8; float g13DC; char pad5[0x13E4 - 0x13E0];
    struct LINK *plink;
};
void func_001A7E10(void *pg, struct LINK *pl);
void *func_001F7530(void *p, int n);
void *func_002333B4(void *p, int c, int cb);
void func_001F7598(struct MSG *pmsg);
float *func_0012F938(void *p, int n);
void func_00130D30(struct Q *p, int n, float g, float h);
void func_00130B18(struct Q *p);
static inline void Zero(struct V3 *pv) { pv->z = 0.0f; pv->y = 0.0f; pv->x = 0.0f; }
static inline qword Bcast(int g) { qword a; __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(a) : "r"(g)); return a; }
void func_001B6DA8(struct P *p, int s)
{
    if (p->x13D8 == s)
        return;
    if (p->x13D8 == -1)
        Zero(&p->v190);
    p->x13D8 = s;
    p->g13DC = D_002DDED0.t;
    switch (s) {
    case 0:
        break;
    case -1:
        func_001A7E10(D_003DD490, p->plink);
        p->plink = 0;
        break;
    case 1: {
        union { qword q; float f[4]; } u;
        qword v, up, d, k, r;
        struct VT *vt;
        v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
        up = D_002A2DC0;
        vt = p->vt;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(k) : "j"(v), "j"(up));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(up), "j"(d));
        k = Bcast(*(int *)&D_002C09A8);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(v) : "j"(v), "j"(d));
        u.q = k;
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(v), "j"(up), "j"(k));
        ((void (*)(void *, qword))vt[35].pfn)((char *)p + vt[35].d, r);
        p->g131C = D_002DDED0.t;
        break;
    }
    case 2: {
        struct LINK *pl;
        Zero(&p->v190);
        for (pl = p->plink; pl; pl = pl->pnext) {
            int i = pl->as[0].x8 != p;
            struct SIDE *pso = &pl->as[1 - i];
            struct SIDE *psm = &pl->as[i];
            void *po = func_001F7530(pso->xC, 4);
            if (po) {
                struct MSG msg;
                func_002333B4(&msg, 0, sizeof(msg));
                msg.x0 = p;
                msg.x4 = psm->x0;
                msg.x8 = po;
                msg.xC = 4;
                msg.x10 = -20;
                msg.v20 = pso->v10;
                msg.v30 = psm->v30;
                func_001F7598(&msg);
            }
        }
        func_001A7E10(D_003DD490, p->plink);
        p->plink = 0;
        {
            float *pg = func_0012F938(p->p1030->x14, 0x1A5);
            if (pg)
                func_00130D30(p->p1030, 0, *pg, 1.0f);
            else
                func_00130B18(p->p1030);
        }
        break;
    }
    }
}
