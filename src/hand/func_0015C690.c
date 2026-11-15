// FireExplsExplso (Claude agent) MATCH: g8 if/else reload form, max via local h=0.5f, pfrm transform split into mul asm + vadd asm with t loaded late.
#include "h2_explso.h"
/* EMITB +8 (SafeHouse: EMITS) - the particle source settings */
typedef struct EMITS { void *ploSource; void *pvKind2; int x8; int xC; void *psoTouch; } EMITS;
typedef struct XF4 { qword v; } XF4;
typedef struct X4 { char pad[0xF4]; XF4 *p; } X4;
typedef struct EMITOLXF { qword pos; qword mat[3]; } EMITOLXF;   /* a frame to burst in: position, rotation rows */
/* the emitter settings block (shared, reference-counted; emitter.h EMITB) */
typedef struct EMITB {
    int cref;
    int emitrk;                 /* the particle kind: 0 blips, 1 RIPs */
    EMITS *pemits;
    int xC;
    int kindPos;                /* the position kind: 0 a point, 1 a box, 2 an object's (pvKind2), 3 a mesh */
    int x14; int x18;
    EMITOLXF *pemitolxf;        /* the frame of a burst (GRFEXPLSO_Olxf) */
    int pad20[4];
    union { qword pos; qword *pbox; EMITS *pemits; struct { char pad[0x20]; qword v; } *pmesh; } u30;   /* by kindPos */
    qword vec;                  /* the direction */
    float g50, g54;             /* scaled by the density limit (speeds?) */
    char pad58[0xD8 - 0x58];
    float sRipD8, sRipDC;       /* the RIPs' size (GRFEXPLSO_Radius) */
    qword vE0[2];               /* scaled by the density (at least 0.5) */
} EMITB;
/* Sly 1 sound.h SFX */
typedef struct SFX { int sfxid; float sStart, sFull, uVol, uPitch; } SFX;
typedef struct LM { float gMin, gMax; } LM;
typedef struct EXPLS {
    char pad[0xE4];
    EMITB *pemitb;
    int xE8, xEC;
    SFX *psfx;                  /* PsfxEnsureExpls */
    LM lmcParticle;             /* the particle count range */
    int fEmitg;                 /* emit into the explosion's own RIP group / particle system */
    void *pripg;                /* field: SafeHouse port */
    void *ppsys;                /* field: SafeHouse port */
} EXPLS;
typedef struct EMITG { void **pppsys; void **ppripg; EXPLS *pexpls; } EMITG;

extern char D_002BDEC0[];
extern float GRandInRange__Fff(float lo, float hi);
extern float GLimitLm(void *p, float g) asm("GLimitLm__FP2LMf");
typedef union V4 { qword q; float a[4]; } V4;
extern V4 __8VU_FLOATf(float g);
extern V4 __9VU_VECTORRC6VECTOR(qword *pv);
extern qword __ml__FG8VU_FLOATG9VU_VECTOR(qword a, qword b);
extern void func_00256D18(qword *pv, qword a);
extern void EmitParticles__FP8EMITTERNP5EMITBP5EMITG(int c, EMITB *pemitb, EMITG *pemitg);
extern qword ConvertPos__FP2LOT0G9VU_VECTOR(void *ploFrom, void *ploTo, qword pos);
extern void *PsndNewPlain__Fi(int sfxid);
extern void SetSource__4CSndPv(void *p, void *pso);
extern void SetPosition__4CSndG9VU_VECTOR(void *p, qword v);
extern void SetFalloff__4CSndff(void *p, float a, float b);
extern void SetVolume__4CSndf(void *p, float g);
extern void SetPitch__4CSndiif(void *p, float g);

/* FireExplsExplso: an explosion's burst: copy its emitter settings, apply the EXPLSO overrides, emit the particles,
 * then play its sound (if any) at the burst position. */
void FireExplsExplso__FP5EXPLSP6EXPLSO(EXPLS *pexpls, EXPLSO *pexplso)
{
    EMITS emits;
    EMITB b;
    EMITG emitg;
    EMITG *pemitg;
    int c;
    V4 pos;
    V4 h;

    emits = *pexpls->pemitb->pemits;
    b = *pexpls->pemitb;
    b.pemits = &emits;
    if (pexplso->grfexplso & GRFEXPLSO_Count)
        c = pexplso->cParticle;
    else
        c = (int)GRandInRange__Fff(pexpls->lmcParticle.gMin, pexpls->lmcParticle.gMax);
    if (pexplso->grfexplso & GRFEXPLSO_Reference)
        emits.ploSource = pexplso->paloReference;
    if (pexplso->grfexplso & GRFEXPLSO_Vec)
        b.vec = pexplso->vec;
    if (pexplso->grfexplso & GRFEXPLSO_Pos) {
        b.u30.pos = pexplso->posOrigin;
        b.kindPos = 0;
    } else if (pexplso->grfexplso & GRFEXPLSO_Olxf) {
        b.pemitolxf = (EMITOLXF *)pexplso->pemitolxf;
    }
    if ((pexplso->grfexplso & GRFEXPLSO_Scale) && b.emitrk == 0) {
        float g;
        float gs;
        int n;
        if (pexplso->rScale == 0.0f)
            g = pexplso->sRadius * 0.01f;
        else
            g = pexplso->rScale;
        if (g < 1.0f)
            c = (int)(c * g);
        else
            c = (int)(c / g);
        n = (int)pexpls->lmcParticle.gMax / 2;
        if (!(n < c))
            c = n;
        gs = GLimitLm(D_002BDEC0, g);
        b.g50 *= gs;
        b.g54 *= gs;
        { float h = 0.5f; g = (h < g) ? g : h; }
        func_00256D18(b.vE0, __ml__FG8VU_FLOATG9VU_VECTOR(__8VU_FLOATf(g).q, __9VU_VECTORRC6VECTOR(b.vE0).q));
    }
    if (b.emitrk == 1) {
        if (pexplso->grfexplso & GRFEXPLSO_Radius)
            b.sRipDC = b.sRipD8 = pexplso->rScale;
        if (pexplso->grfexplso & GRFEXPLSO_Touch)
            b.pemits->psoTouch = pexplso->psoTouch;
    }
    if (pexpls->fEmitg) {
        emitg.pppsys = &pexpls->ppsys;
        emitg.ppripg = &pexpls->pripg;
        emitg.pexpls = pexpls;
        pemitg = &emitg;
    } else {
        pemitg = 0;
    }
    if (emits.ploSource == 0 && b.kindPos != 2 && !(pexplso->grfexplso & (GRFEXPLSO_Scale | GRFEXPLSO_Olxf)))
        emits.ploSource = pexpls;
    EmitParticles__FP8EMITTERNP5EMITBP5EMITG(c, &b, pemitg);
    if (pexpls->psfx) {
        void *ps;
        switch (b.kindPos) {
        case 0:
            pos.q = b.u30.pos;
            break;
        case 1: {
            float half = 0.5f;
            {
                register qword hv __asm__("vf1");
                __asm__("qmtc2.ni %1, %0" : "=j"(hv) : "r"(half));
                h.q = hv;
                {
                    qword *pm = b.u30.pbox;
                    register qword m1 __asm__("vf2") = pm[1];
                    register qword m0 __asm__("vf3") = pm[0];
                    register qword r __asm__("vf1");
                    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(m0), "j"(m1), "j"(hv));
                    pos.q = r;
                }
            }
            break;
        }
        case 2:
            pos.q = ((X4 *)b.pemits->pvKind2)->p->v;
            break;
        case 3:
            pos.q = b.u30.pmesh->v;
            break;
        }
        if (b.pemitolxf) {
            EMITOLXF *pf = b.pemitolxf;
            qword *pm = pf->mat;
            register qword v __asm__("vf3") = pos.q;
            register qword m0 __asm__("vf4") = pm[0];
            register qword m1 __asm__("vf1") = pm[1];
            register qword m2 __asm__("vf5") = pm[2];
            __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "0"(v), "j"(m0), "j"(m1), "j"(m2));
            {
            register qword t __asm__("vf2") = pf->pos;
            __asm__("vadd.xyzw %0, %0, %1" : "=j"(v) : "j"(t), "0"(v));
            }
            pos.q = v;
        }
        pos.q = ConvertPos__FP2LOT0G9VU_VECTOR(emits.ploSource, 0, pos.q);
        ps = PsndNewPlain__Fi(pexpls->psfx->sfxid);
        SetSource__4CSndPv(ps, 0);
        SetPosition__4CSndG9VU_VECTOR(ps, pos.q);
        SetFalloff__4CSndff(ps, pexpls->psfx->sStart, pexpls->psfx->sFull);
        SetVolume__4CSndf(ps, pexpls->psfx->uVol);
        SetPitch__4CSndiif(ps, pexpls->psfx->uPitch);
    }
}
