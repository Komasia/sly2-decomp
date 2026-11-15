/* CacheSegCrv: cache the sub-lengths of segment iseg of a cubic curve: eleven Hermite samples at parameter
 * fractions 0, 0.1, ..., 1 (the points and tangents transformed by the curve's world matrix amat) and the cumulative
 * lengths between them (asSub; the last is the segment's length). Layout: crv.h CRV, as this file declares it (a
 * local copy with its own matrix struct). */
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f; };
struct M4 { qword a, b, c, d; };
struct CRV {
    char pad[0xEC];
    float *ag;       // 0xEC, the parameters
    float *as;        // 0xF0, the distances
    qword *apos;      // 0xF4, the points
    char padF8[8];
    struct M4 amat;      // 0x100
    qword *avIn;          // 0x140, the incoming tangents
    qword *avOut;         // 0x144, outgoing tangents
    int isegCached;        // 0x148, the segment cached (-1: none)
    float asSub[11];  // 0x14C
};
void Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(float duration, float t, float scale, qword start, qword startTangent, qword end, qword endTangent,
                   qword *pos, qword *vel, qword *acc);

static inline qword Dir(qword m0, qword m1, qword m2, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
            : "=j"(r) : "j"(m0), "j"(m1), "j"(m2), "j"(v));
    return r;
}
static inline qword Point(qword m0, qword m1, qword m2, qword m3, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m0), "j"(m1), "j"(m2), "j"(m3), "j"(v));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Len(qword a)
{
    qword one;
    float f;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(a), "=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(a));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(a));
    return f;
}

// name: SafeHouse port (CacheSegCrv)
void CacheSegCrv__FP3CRVi(struct CRV *pcrv, int iseg)
{
    union U prev, cur;
    // Plain qwords: they live across the call in the loop, so reload spills them to 0x20..0x50 and
    // loads them straight into the argument registers.
    qword start, end, a, b;
    int j;
    float duration;
    if (iseg == pcrv->isegCached)
        return;
    {
        struct M4 *m = &pcrv->amat;
        qword v0 = pcrv->apos[iseg], v1 = pcrv->apos[iseg + 1], o0 = pcrv->avOut[iseg], i1 = pcrv->avIn[iseg + 1];
        qword m1 = m->b, m2 = m->c, m3 = m->d, m0 = pcrv->amat.a;
        pcrv->asSub[0] = 0;
        // Computed in argument order; the scheduler then emits them as b, end, start, a.
        start = Point(m0, m1, m2, m3, v0);
        a = Dir(m0, m1, m2, o0);
        end = Point(m0, m1, m2, m3, v1);
        b = Dir(m0, m1, m2, i1);
    }
    duration = pcrv->ag[iseg + 1] - pcrv->ag[iseg];
    for (j = 0; j < 11; j++) {
        float frac = (float)j * 0.1f;
        Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(duration, frac * duration, 1.0f, start, a, end, b, &cur.q, 0, 0);
        if (j > 0)
            pcrv->asSub[j] = pcrv->asSub[j - 1] + Len(Sub(prev.q, cur.q));
        prev.q = cur.q;
    }
    pcrv->isegCached = iseg;
}
