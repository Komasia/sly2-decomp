typedef int qword __attribute__((mode(TI)));
#define F(T, o) (*(T *)((char *)p + (o)))
#define A(o) ((char *)p + (o))

struct LO { char pad[0x28]; int x28; signed char x2C; char x2D; long k:4; long :8; unsigned int f:1; };
struct X150 { char pad[0x18]; float g18; };
struct X1854 { char pad[0x124]; int x124; };
typedef union { qword q; float f[4]; } VU;


extern float D_002BF3D4;
extern float D_002BF3D8;
#define GI(x) (*(int *)&(x))

extern float D_002BF3DC;

extern void func_001403D0(void *p);
extern void func_0018B7E8(void *p);
extern void func_00204660(void *p, float g);
extern void func_0020BB58(void *p, float g);
extern void func_0020BC08(void *p);
extern void func_001A0450(void *p, void *a, int b);
extern void func_0018A0C8(void *p);
extern void func_00190E18(void *p);
extern void func_00185E40(void *p);
extern void func_0018DF60(void *p);

extern void func_00189C40(void *p, int a, float g, int b, int c, void *d);
#define C40(p,a,b,c,d,g) func_00189C40(p,a,g,b,c,d)

extern void func_00189EC8(void *p, void *a, int b);
extern void func_0018ED70(void *p);
extern int func_00132B10(void *p, int n);
extern void func_001E7380(void *p, qword q, int a, qword *pv, int b, int c, int d, float g);
extern void func_0018C250(void *p, int a, int b);
extern qword func_001A62E8(void *p);
extern void func_0011E7C8(qword a, qword b, qword c, qword d, void *pv, float *pg, void *pv2);
extern void func_00189618(void *p);

static __inline__ qword Bc(int g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static __inline__ qword BcF(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static __inline__ qword VMulX(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s)); return r; }

void func_0018BCE0(char *p)
{
    VU u;
    qword av[3];
    VU w;
    float ag[4];
    int i;
    struct X1854 *po;

    func_001403D0(p);
    if (!((struct LO *)p)->f)
        return;
    if (F(void *, 0x150))
        func_0018B7E8(p);
    switch (F(int, 0x18C8)) {
    case 1: {
        qword s;
        func_00204660(p, F(struct X150 *, 0x150)->g18);
        func_0020BB58(A(0x1320), 1.0f);
        func_0020BC08(A(0x1320));
        
s = Bc(GI(D_002BF3D4)); u.q = s; F(qword, 0x190) = VMulX(F(qword, 0x190), s);

        break;
    }
    case 5:
        if (F(int, 0x18D0) == 5) {
            qword s;
            func_001A0450(p, A(0x13D0), F(int, 0x14D0));
            
s = Bc(GI(D_002BF3D8)); u.q = s; F(qword, 0x190) = VMulX(F(qword, 0x190), s);

            F(float, 0x180) = 1.0f;
        }
        break;
    case 0xA:
        func_001A0450(p, A(0x1AC0), F(int, 0x1BC0));
        break;
    case 0:
        func_0018A0C8(p);
        break;
    case 3:
        func_00190E18(p);
        break;
    case 0xC:
        func_0020BC08(A(0x1C30));
        break;
    case 0x15:
        func_00185E40(p);
        break;
    case 0x16:
        func_0018DF60(p);
        break;
    case 0x18:
        if (F(int, 0x19F0)) {
            C40(p, F(int, 0x19D8), F(int, 0x19E0), F(int, 0x19F0), A(0x1520), D_002BF3DC);
            C40(p, F(int, 0x19D4), F(int, 0x19DC), F(int, 0x19F4), A(0x1620), D_002BF3DC);
            func_00189EC8(p, A(0x1520), F(int, 0x19F0));
            func_00189EC8(p, A(0x1620), F(int, 0x19F4));
        }
        break;
    }
    func_0018ED70(p);
    if (F(int, 0x18D8) == 0) {
        if (func_00132B10(F(void *, 0x1854), 0xB)) {
            void *po2 = F(void *, 0x1854);
            for (i = 0; i < 3; i++)
                func_001E7380(po2, ((qword *)A(0x1890))[i], 0, &av[i], 0, 0, 0, F(float, 0x1858));
            goto loop;
        L16:
            func_0018C250(p, 0x16, -1);
            goto end;
        } else {
            qword q;
            if (!func_00132B10(F(void *, 0x1854), 0x13))
                goto end;
            q = func_001A62E8(F(void *, 0x1854));
            av[2] = q;
            av[1] = q;
            av[0] = q;
        }
    loop:

        for (i = 1; i < F(int, 0x1880); i++) {
            qword *aq = (qword *)A(0x1890);
            func_0011E7C8(aq[i - 1], aq[i], av[i - 1], av[i], &u, ag, &w.q);

            if (ag[0] < F(float, 0x19AC)) {
                if (func_00132B10(F(void *, 0x1854), 0x13)) {
                    po = F(struct X1854 *, 0x1854);
                    F(struct X1854 *, 0x18C4) = po;
                    if (po->x124 == 3)
                        goto L16;
                    func_0018C250(p, 3, 1);
                } else {
                    F(void *, 0xF5C) = F(void *, 0x1854);
                    F(float, 0xF60) = F(float, 0x1858);
                    func_0018C250(p, 8, -1);
                }
                break;
            }
        }
    }
end:
    func_00189618(p);
}
