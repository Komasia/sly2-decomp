typedef int qword __attribute__((mode(TI)));
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
typedef union { qword q; struct { float x, y, z, w; } v; } UQ;
struct LO { char pad[0xE8]; int c; char pad2[8]; qword *aq; };
struct E { qword a, b; char pad[0x40]; };
extern float D_002A76DC;
void *func_001BF110(void *p, qword pos, int fl);
qword func_001BFDB0(void *p, qword pos);
int func_001C1700(void *p, int a, qword q0, qword q1, int c, void **apv);
int func_001BC9F0(void *p, qword pos);
qword func_001A6F00(struct LO *p, int a, qword q);
int func_001C0960(void *p, qword a, qword b, int n, struct E *ae, int c);
void func_0011EE08(qword q, qword a, qword b, qword *pq, int n, float *pf);
void func_001C0940(void *p, qword q, qword *pq, int n);

int func_001C0B50(char *p, qword pos, qword *pqOut)
{
    void *apv[0x80];
    UQ a, b;
    UQ best;
    struct E ae[1];
    qword out;
    float f;
    void *pv;
    qword q;
    struct LO *plo;
    int i, n;
    float fMin;

    pv = func_001BF110(p + 0xE0, pos, 1);
    if (!pv)
        return 0;
    q = func_001BFDB0(pv, pos);
    plo = 0;
    n = func_001C1700(p, 0, q, q, 0x80, apv);
    for (i = 0; i < n; i++) {
        if (func_001BC9F0(apv[i], pos)) {
            plo = apv[i];
            break;
        }
    }
    if (!plo) {
        *pqOut = q;
        return 1;
    }
    best.v.z = 0.0f;
    best.v.y = 0.0f;
    best.v.x = 0.0f;
    fMin = D_002A76DC;
    i = 1;
    a.q = func_001A6F00(plo, 0, plo->aq[0]);
    a.v.z = GetZ(q);
    for (; i < plo->c; i++) {
        int c, j;
        struct E *pe;
        b.q = func_001A6F00(plo, 0, plo->aq[i]);
        b.v.z = GetZ(q);
        c = func_001C0960(p, a.q, b.q, 1, ae, 2);
        for (j = 0; j < c; j++) {
            func_0011EE08(q, ae[j].a, ae[j].b, &out, 0, &f);
            if (f < fMin) {
                fMin = f;
                best.q = out;
            }
        }
        a = b;
    }
    func_001C0940(p, best.q, pqOut, 0);
    return 1;
}
