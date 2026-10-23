/* Hermite rotation interpolation (mat0,w0)->(mat1,w1) over dt at t: optional M3 out (t0) and scaled angular velocity out (t1).
   Diff 108/207: frame 0x20 too big (Mul return temps at 0xD0/0x100 vs target 0x60/0xD0), pmat0/pmat1 s-reg swap, pwOut scalar scheduling. */
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3];M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
extern "C" M3 *func_0011B570(M3 *,qword);
extern "C" M3 *func_0011BC00(M3 *,M3 *,M3 *);
extern "C" qword func_0011BFB8(M3 *);
static inline M3 BuildRotation(qword vector) return matrix {func_0011B570(&matrix,vector);}
static inline M3 Relative(M3 *a, M3 *b) return matrix {func_0011BC00(&matrix,a,b);}
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return out->q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(r):"j"(v),"j"(k));return r;}
static inline M3 Mul(const M3 &a,const M3 &b) return m
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r0):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[0].q));
    t.r[0].q = r0; m.r[0].q = r0;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r1):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[1].q));
    t.r[1].q = r1; m.r[1].q = r1;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r2):"j"(a.r[0].q),"j"(a.r[1].q),"j"(a.r[2].q),"j"(b.r[2].q));
    t.r[2].q = r2; m.r[2].q = r2;
}

/* Hermite interpolation of a rotation: matrices pmat0/pmat1 with angular velocities w0/w1 over duration dt,
   evaluated at t; outputs the matrix (optional) and the angular velocity scaled by gScale (optional). */
extern "C" void func_00117308(float dt, float t, float gScale, M3 *pmat0, qword w0, M3 *pmat1, qword w1, M3 *pmatOut, qword *pwOut)
{
    float u = t / dt;
    float v = 1.0f - u;
    if (pmatOut) {
        float u2 = u * u;
        float h2 = u2 * v;
        float u3 = u2 * u;
        M3 a, b, rel, rot;
        U s;
        func_0011B570(&rot, Scale(w0, Scalar(u * v * v * dt, &s)));
        a = Mul(rot, *pmat0);
        func_0011B570(&rot, Scale(w1, Scalar(-h2 * dt, &s)));
        b = Mul(rot, *pmat1);
        {
            qword w;
            func_0011BC00(&rel, &a, &b);
            w = func_0011BFB8(&rel);
            func_0011B570(&rot, Scale(w, Scalar(h2 * (3.0f - dt) + u3, &s)));
            *pmatOut = Mul(rot, a);
        }
    }
    if (pwOut) {
        M3 rel;
        U s;
        U k;
        qword w, r, ka, kb, kc, sc;
        float g = u * (6.0f - u * 6.0f) / dt;
        float h = u * 3.0f;
        k.q = *(int *)&g;
        func_0011BC00(&rel, pmat0, pmat1);
        w = func_0011BFB8(&rel);
        sc = Scalar(gScale, &s);
        ka = Scalar(1.0f - u * (4.0f - h), &s);
        kb = Scalar(u * (h + -2.0f), &s);
        __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddax.xyzw $ACC,%3,%4x\n\tvmaddx.xyzw %0,%5,%6x":"=&j"(r):"j"(w),"j"(k.q),"j"(w0),"j"(ka),"j"(w1),"j"(kb));
        *pwOut = Scale(r, sc);
    }
}
