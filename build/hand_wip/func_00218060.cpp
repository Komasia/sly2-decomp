typedef int qword __attribute__((mode(TI)));
struct RGBA2 { unsigned char r, g, b, a; };
struct RGBA {
    unsigned char r, g, b, a;
    RGBA() {}
    RGBA(const RGBA &c) { *(RGBA2 *)this = *(const RGBA2 *)&c; }
} __attribute__((aligned(16)));
struct QQ { qword a, b; };
struct Y { RGBA2 c0; RGBA2 c1; char pad8[8]; QQ q; };
struct E { char pad[8]; short h8; short hA; float fC; int x10; int x14; };
struct F { char pad[8]; float f8; char padc[0xC]; };
struct S;
struct A { int x0; F *af; E *ae; char padc[0x18]; S *ps; char pad28[8]; };
struct S { char pad[0x84]; A *aa; };
extern "C" int func_00213E20(S *p, int k, QQ *pq, RGBA *pc0, RGBA *pc1, int c, void *ay);
extern "C" void func_00217F38(A *p, int i);
extern "C" void func_002183E8(A *p, int i, QQ *pq, float g, RGBA c0, RGBA c1);
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
extern "C" void func_00218060(A *p, int i, Y *py, float g)
{
    QQ q;
    RGBA c0, c1;
    int h = p->ae[i].h8;
    if (h < 0)
        return;
    g = GMin(p->af[h].f8, GMax(0.0f, g));
    if (py) {
        q = py->q;
        *(RGBA2 *)&c0 = py->c0;
        *(RGBA2 *)&c1 = py->c1;
    } else if (!func_00213E20(p->ps, p - p->ps->aa, &q, &c0, &c1, 0, 0)) {
        return;
    }
    func_00217F38(p, i);
    p->ae[i].fC = 0.0f;
    p->ae[i].hA = 0;
    p->ae[i].x10 = 0;
    func_002183E8(p, i, &q, 0.0f, c0, c1);
    p->ae[i].x10 = 0;
    func_002183E8(p, i, &q, g, c0, c1);
    p->ae[i].x10 = 1;
}
