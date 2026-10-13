// Compute the hit span and optional intersection outputs.
typedef int qword __attribute__((mode(TI)));
typedef struct MSG { int cb; int nKind; } MSG;
typedef struct MARK { int a[4]; } MARK;
struct LSG { char pad[0x10]; qword pos; char pad1[0x10]; qword normal; float g40; float g44; char pad2[0x18]; };
struct X { char pad[8]; float g8; char pad1[0xC]; float g18; };
struct J { char pad[0xEC]; struct X *px; char pad1[0x208 - 0xF0]; int x208; char pad2[0x238 - 0x20C]; float g238; char pad3[0xC]; float g248; };
struct S { char pad[0xE0]; int c; };
extern qword D_002A2DC0;
extern qword D_002A2DD0;
MARK *func_001AE478(MARK *pm);
void func_001AE4A0(MARK *pm, int n);
void *func_001AE318(MSG *pmsg);
qword func_001A62E8(void *p);
int func_00132B10(struct J *pj, int k);
int func_00229D60(void *,void *);
int func_001F7E08(struct S *p,int (*pfn)(void *,void *),void *context,void **apv);
int func_0014CDB0(qword a, qword b, int cso, void **apso, int cMax, struct LSG *alsg);
int func_0011D4D0(float a, float b, float eps);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline float Epsilon(){register float f __asm__("$f14");__asm__ __volatile__("li.s %0,%1":"=f"(f):"F"(1e-4f));return f;}
static inline int WordY(qword q){int r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return r;}
static inline int WordZ(qword q){int r;__asm__("pextuw %0,$0,%1":"=r"(r):"r"(q));return r;}
static inline float FloatWord(int word){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline int NearX(qword d,qword n,float e){return func_0011D4D0(GetX(d),GetX(n),e);}
static inline int NearY(qword d,qword n){int y=WordY(d);float e=Epsilon();return func_0011D4D0(FloatWord(y),GetY(n),e);}
static inline int NearZ(qword d,qword n){int z=WordZ(d);float e=Epsilon();return func_0011D4D0(FloatWord(z),GetZ(n),e);}
float func_00229468(struct S *p, struct J *pj, qword *ppos, qword *pnormal)
{
    union { qword q; float f[4]; } a, b;
    MARK mark;
    MSG msg;
    void **apv;
    int c;
    struct LSG alsg[0x10];
    float g;
    a.q = b.q = func_001A62E8(pj);
    if (func_00132B10(pj, 0x33)) {
        a.f[2] = a.f[2] + pj->g248;
        if (pj->x208)
            a.f[2] = a.f[2] > pj->g238 ? a.f[2] : pj->g238;
    } else {
        a.f[2] = pj->px->g8;
    }
    b.f[2] = pj->px->g18;
    func_001AE478(&mark);
    {
        MSG *pm = &msg;
        pm->cb = p->c * 4;
        pm->nKind = 0x10;
        apv = func_001AE318(pm);
    }
    c = func_001F7E08(p, func_00229D60, 0, apv);
    if (!func_0014CDB0(a.q, b.q, c, apv, 0x10, alsg)) {
        if (pnormal)
            *pnormal = D_002A2DC0;
        func_001AE4A0(&mark, 2);
        return 0.0f;
    }
    if (ppos)
        *ppos = alsg[0].pos;
    if (pnormal) {
        qword n = alsg[0].normal;
        qword d;
        float epsilon=Epsilon();
        int f;
        *pnormal = n;
        d = D_002A2DD0;
        f = NearX(d,n,epsilon) && NearY(d,n) && NearZ(d,n);
        if (f)
            *pnormal = D_002A2DC0;
    }
    g = alsg[0].g44 - alsg[0].g40;
    func_001AE4A0(&mark, 2);
    return g;
}
