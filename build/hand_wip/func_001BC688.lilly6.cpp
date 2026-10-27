// func_001BC688 near-miss (lilly6, T1817): 8/217, aligned 8, NO register pin. = lilly5 without the pin on i.
// Left: i in s1 / plane copy in s0 (game: s0 / s1); global-alloc ranks the 4-ref asm copy above i. See lilly5 / notes.
typedef int qword __attribute__((mode(TI)));
struct VU_QWORD { qword qw; VU_QWORD(); };
struct VU_FLOAT { qword qw; };
struct SURF;
struct LSG {
    qword apos[2];
    qword anormal[2];
    float au[2];
    int lsgk;
    void *apsurf[2];
    void *pedge;
    int iiposSwap;
    LSG *plsgNext;
};
struct CNVO { char pad[0xE8]; int cplane; char pad2[0x1EC - 0xEC]; qword *aplane; };
extern "C" {
void func_001BD400(CNVO *p);
void *func_002333B4(void *, int, unsigned);
extern float D_002C0AB4;
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline qword QwMix(VU_FLOAT g1, const qword &qw1, VU_FLOAT g2, const qword &qw2)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %4x" : "=j"(qw) : "j"(qw1), "j"(qw2), "j"(g1.qw), "j"(g2.qw));
    return qw;
}
static inline qword QwZero() { qword qw; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(qw)); return qw; }
static inline qword QwNeg(qword v) { qword qw; __asm__("vsub.xyzw %0, $vf0, $vf0\n\tvsub.xyzw %0, %0, %1" : "=&j"(qw) : "j"(v)); return qw; }

extern "C" int func_001BC688(CNVO *pcnvo, qword pos1, qword pos2, int clsgMax, LSG *alsg)
{
    func_001BD400(pcnvo);
    float gIn = 0.0f;
    qword normalIn = QwZero();
    float gOut = 1.0f;
    qword normalOut = normalIn;
    int i;
    for (i = 0; i < pcnvo->cplane - 1; i++) {
        qword plane = pcnvo->aplane[i];
        qword normal;
        __asm__("" : "=r"(normal) : "0"(plane)); /* empty asm: the game keeps this copy (lq s1,0x70) for the else branch */
        VU_QWORD dot1;
        VU_QWORD vfOne1;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
                : "=j"(dot1), "=j"(vfOne1) : "j"(plane), "j"(pos1));
        float g1 = GFromVf(dot1.qw);
        VU_QWORD dot2;
        VU_QWORD vfOne2;
        g1 += D_002C0AB4;
        float g2;
        __asm__ __volatile__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
                : "=j"(vfOne2), "=j"(dot2) : "j"(plane), "j"(pos2));
        __asm__("mtc1 %1,%0" : "=f"(g2) : "r"(dot2.qw), "j"(dot2.qw), "j"(vfOne2.qw), "j"(vfOne2.qw));
        g2 += D_002C0AB4;
        if (g1 < 0.0f && g2 < 0.0f)
            continue;
        if (g1 > 0.0f && g2 > 0.0f) {
            gIn = gOut = 0.0f;
            break;
        }
        float t = g1 / (g1 - g2);
        if (g1 < 0.0f) {
            gOut = (gOut < t) ? gOut : t;
            normalOut = plane;
        } else {
            normalIn = normal;
            gIn = (t < gIn) ? gIn : t;
        }
        if (gOut <= gIn)
            break;
    }
    int clsg = 0;
    LSG *plsg;
    if (gOut <= gIn && clsg < clsgMax) {
        plsg = &alsg[clsg++];
        func_002333B4(plsg, 0, sizeof(LSG));
        plsg->apos[0] = pos1;
        plsg->au[1] = 1.0f;
        plsg->apos[1] = pos2;
        plsg->au[0] = 0.0f;
    } else {
    if (gIn > 0.0f && clsg < clsgMax) {
        plsg = &alsg[clsg++];
        func_002333B4(plsg, 0, sizeof(LSG));
        plsg->apos[0] = pos1;
        plsg->apos[1] = QwMix(VuFloat(1.0f - gIn), pos1, VuFloat(gIn), pos2);
        plsg->anormal[1] = QwNeg(normalIn);
        plsg->au[0] = 0.0f;
        plsg->au[1] = gIn;
        plsg->apsurf[1] = pcnvo;
    }
    if (gOut < 1.0f && clsg < clsgMax) {
        plsg = &alsg[clsg++];
        func_002333B4(plsg, 0, sizeof(LSG));
        plsg->apos[0] = QwMix(VuFloat(1.0f - gOut), pos1, VuFloat(gOut), pos2);
        plsg->anormal[0] = QwNeg(normalOut);
        plsg->apos[1] = pos2;
        plsg->au[0] = gOut;
        plsg->au[1] = 1.0f;
        plsg->apsurf[0] = pcnvo;
    }
    }
    return clsg;
}
