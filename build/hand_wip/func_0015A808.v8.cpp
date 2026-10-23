// (Claude agent, lane E9) v8: aligned 1 (v7 probe 3, v6 11), no asm probe: the freed 48-byte slot comes from an UNUSED block-local VU_VECTOR[3] in case 1 (case-1 locals are freed and reused by case 3: an[] lands at 0x30, w temp at 0x60). Same at dummy[2]/[1] = 11; float[12] / MATRIX3 also 1. Left: D_002A2DA0 lq (target after VLen; moving k after VLen = 2, consts then hoisted) and dir/pos spill slots swapped (0x70/0x80; masked in aligned).
// (Claude agent, lane E8) v7: aligned 3 (v6 11). PROBE, not matchable as is: a freed 48-byte block temp right before the first Combo3
// ({ VU_VECTOR dummy[3]; asm("" : : "m"(dummy[0])); }) gives the target's slots: an[] at 0x30..0x50, w temp stored at 0x60. Need the natural source for that slot.
// (Claude agent, lane E6) v6: aligned 11 (v5 20): av[] in a block around the first switch (final VU_FLOAT temp now at sp+0 like the target); VLen split into two asms, outputs (one "=j", l "=&j") then "+j"(l) vadday/vmaddz with a "memory" clobber (fixes VF numbering + const schedule). Left: the missing w VU_FLOAT store at 0x60 in the kindDir==5 block (1 insn -> 9 branch offsets), lq of D_002A2DA0 placement.
// (Claude agent, lane E5) v5: aligned 20 (v4 38): MulTMat as ONE volatile asm, outputs (d "=j", one, t0, t1, t2 "=&j") -> target load order and VF numbers. v4 38 (v3 51): zero stores pf[2],pf[1],pf[0] (target order 0,8,4); D_002DDF40 matrix through an inline MulCam(CM *pcm, v) (target forms &D then +0x60 per path); "=&j" outputs on MulTMat vmuls. Left: tri-normal temps (target an[] at 0x30..0x50 + w VU_FLOAT temp at 0x60), MulTMat VF numbering, 1-insn shift.
// (Claude agent, lane E4) v3: aligned 51 (v2 54): frame now 0x140 (= target): function-scope VU_VECTOR av[3] shared with the case-2 normal, p->ep.v40 in the Cross, plain qword vdiv output, nop before vdiv.
// (Claude agent, lane E3) v2: aligned 54 (was 66): tri normals copied into a VU_VECTOR an[3] array before Combo3.
// WIP func_0015A808 (EMITB choose emit pos/dir): 171/335 differ. Structure/branch layout/call order right; left: frame 0x130 vs 0x140,
// p/ppos/pep reg alloc swap (s2/s3/s4), tri-normal VU_VECTOR temps (target stores n0..n2,w at sp+0x30..0x60), mesh normal temp slot.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; };
static inline VU_VECTOR V(qword q) { VU_VECTOR v; v.q = q; return v; }
struct MATRIX3 { qword r[3]; };
struct CM { char pad[0x60]; MATRIX3 mat; };
extern CM D_002DDF40;
extern qword D_002A2DA0;
struct TRI { int aipos[3]; float sArea; };
struct EMITMESH { int cpos; qword *apos; int ctri; TRI *atri; qword *anormal; float sArea; };
struct BOXE { float xMin, yMin, zMin, pad; float xMax, yMax, zMax; };
struct MESHO { char pad[0xE8]; int cs; int padEC; float *as; };
struct EMITO { void *palo; MESHO *pmesh; };
struct LM { float gMin, gMax; };
struct EP {
    int kind;
    int kindDir;
    int pad18[3];
    LM lm;
    int pad2C;
    void *pv30;
    int pad34[3];
    qword v40;
};
struct EMITB {
    int pad0, pad4;
    EMITO *pemito;
    int padC;
    struct EP ep;
};
extern "C" {
float func_0011D448(float gMin, float gMax);
void func_001E6F10(MESHO *pmesh, float g, qword *ppos, qword *pnormal);
MATRIX3 *func_001A6318(void *palo);
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Cross(qword a, qword b)
{
    qword d;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline qword Combo3(VU_FLOAT f0, VU_VECTOR v0, VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword d;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddax.xyzw $ACC, %4, %3x\n\tvmaddx.xyzw %0, %6, %5x"
            : "=j"(d) : "j"(f0.q), "j"(v0.q), "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return d;
}
static inline qword MulMat(const MATRIX3 &m, qword v)
{
    qword d;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(d) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return d;
}
static inline qword MulTMat(const MATRIX3 &m, qword v)
{
    qword d, one, t0, t1, t2;
    __asm__ __volatile__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\t"
            "vadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(d), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return d;
}
static inline qword MulCam(CM *pcm, qword v) { return MulMat(pcm->mat, v); }
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w" : "=j"(one), "=&j"(l) : "j"(c));
    __asm__("vadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(l) : "j"(one) : "memory");
    {
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "0"(l));
    return r;
    }
}
static inline qword Scale(VU_FLOAT f, VU_VECTOR v) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v.q)); return r; }

extern "C" void func_0015A808(EMITB *p, int i, int c, qword *ppos, qword *pv)
{
    EP *pep = &p->ep;
    LM *plm;
    {
    VU_VECTOR av[3];
    switch (p->ep.kind) {
    case 0:
        *ppos = *(qword *)&pep->pv30;
        break;
    case 1: {
        { VU_VECTOR avUnused[3]; } // unused 48-byte local: frees the slot an[] reuses in case 3
        BOXE *pbox = (BOXE *)pep->pv30;
        float *pf = (float *)ppos;
        pf[0] = func_0011D448(pbox->xMin, pbox->xMax);
        pf[1] = func_0011D448(pbox->yMin, pbox->yMax);
        pf[2] = func_0011D448(pbox->zMin, pbox->zMax);
        break;
    }
    case 2: {
        MESHO *pmesh = p->pemito->pmesh;
        if (!pmesh) {
            float *pf = (float *)ppos;
            pf[2] = 0.0f;
            pf[1] = 0.0f;
            pf[0] = 0.0f;
            return;
        }
        float ds = pmesh->as[pmesh->cs - 1] / (float)c;
        float s = (float)i * ds;
        float g = func_0011D448(s, s + ds);
        switch (pep->kindDir) {
        default:
            func_001E6F10(pmesh, g, ppos, 0);
            break;
        case 2:
            func_001E6F10(pmesh, g, ppos, pv);
            goto normalize;
        case 3: {
            func_001E6F10(pmesh, g, ppos, &av[0].q);
            *pv = Cross(av[0].q, p->ep.v40);
            goto normalize;
        }
        }
        break;
    }
    case 3: {
        EMITMESH *pem = (EMITMESH *)pep->pv30;
        float s = func_0011D448(0.0f, 1.0f) * pem->sArea;
        TRI *ptri;
        int itri;
        for (itri = 0; itri < pem->ctri; itri++) {
            ptri = &pem->atri[itri];
            s -= ptri->sArea;
            if (s <= 0.0f)
                break;
        }
        av[0].q = pem->apos[ptri->aipos[0]];
        av[1].q = pem->apos[ptri->aipos[1]];
        av[2].q = pem->apos[ptri->aipos[2]];
        float u = func_0011D448(0.0f, 1.0f);
        float v = func_0011D448(0.0f, 1.0f - u);
        float w = 1.0f - u - v;
        *ppos = Combo3(u, av[0], v, av[1], w, av[2]);
        if (pep->kindDir == 5) {
            VU_VECTOR an[3];
            an[0].q = pem->anormal[ptri->aipos[0]];
            an[1].q = pem->anormal[ptri->aipos[1]];
            an[2].q = pem->anormal[ptri->aipos[2]];
            *pv = Combo3(u, an[0], v, an[1], w, an[2]);
            goto normalize;
        }
        break;
    }
    }

    switch (pep->kindDir) {
    case 0:
        *pv = pep->v40;
        break;
    case 1:
        *pv = Sub(*ppos, pep->v40);
        break;
    case 4: {
        void *palo = p->pemito->palo;
        if (palo) {
            MATRIX3 *pm = func_001A6318(palo);
            *pv = MulTMat(*pm, MulCam(&D_002DDF40, pep->v40));
        } else {
            *pv = MulCam(&D_002DDF40, pep->v40);
        }
        break;
    }
    default:
        *pv = D_002A2DA0;
        break;
    }
    }

normalize:
    plm = &p->ep.lm;
    {
        qword d = *pv;
        qword k = D_002A2DA0;
        qword l = VLen(d);
        float gl;
        VU_VECTOR dir;
        __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
        if (gl < 1e-4f) {
            dir.q = k;
        } else {
            qword dq;
            __asm__ __volatile__("nop\n\tvdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dq) : "j"(d), "j"(l));
            dir.q = dq;
        }
        *pv = dir.q;
        qword pos = *ppos;
        *ppos = Add(pos, Scale(VU_FLOAT(func_0011D448(pep->lm.gMin, plm->gMax)), dir));
    }
}
