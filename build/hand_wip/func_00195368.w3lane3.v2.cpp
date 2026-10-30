// w3lane3 v2: aligned 9 (only produced/ageOut s3<->s4 swap left). Natural C++: VU_FLOAT/VU_VECTOR helpers, GRand(LM*), block-scoped sample locals, giv-producing pointer forms. operator* / AddScaled keep one commented allocation-only duplicate "j" input each (VU numbering).
typedef int qword __attribute__((mode(TI)));
union VECTOR { qword q; float f[4]; };
static inline int Bits(float f) { union { float f; int i; } u; u.f = f; return u.i; }
struct VU_FLOAT { qword q; VU_FLOAT() {} VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(Bits(f))); } };
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(qword a) { q = a; } VU_VECTOR(const VECTOR &v) { q = v.q; } };
struct VT { short delta, pad; void *fn; };
struct SAMPLE { char pad[0x20]; VT *vt; };
struct SOURCE { int reserved; SAMPLE *sample; int reserved8, id; int reserved10, reserved14; float parameter; char pad[0x30 - 0x1C]; };
struct LM { float gMin, gMax; };
struct EMITB { LM lmScale; char pad8[0x3C - 8]; float life; char pad40[8]; LM lmOffset, lmAge; };
struct REP { char pad[0x50]; EMITB emitb; };
struct EMITTER { char pad[0xE0]; int dirty; REP *rep; char padE8[0xFC - 0xE8]; float rate; char pad100[0x150 - 0x100]; void *instance; };
struct P { char pad[0x12F8]; EMITTER *emitter; };
struct EMITX { void **ppinstance; int reserved; EMITTER *pemitter; };
struct CLOCK { float t, dt; };
extern "C" {
extern CLOCK D_002DDED0;
float func_0011D448(float, float);
void *func_002333B4(void *, int, unsigned int);
void func_0015B428(REP *, EMITX *, int, VECTOR *, VECTOR *, float *, float *, void *, void *);
}
void OnEmitterValuesChanged(EMITTER *);
static inline float GRand(LM *plm) { return func_0011D448(plm->gMin, plm->gMax); }
static inline VU_VECTOR operator*(VU_FLOAT s, VU_VECTOR v) { __asm__("vmulx.xyzw %0,%0,%1x" : "+j"(v.q) : "j"(s.q), "j"(v.q)); return v; }
static inline VU_VECTOR AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s) { __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "+j"(a.q) : "j"(b.q), "j"(s.q), "j"(b.q)); return a; }
static inline void SampleSource(SOURCE *psource, VECTOR *ppos, VECTOR *pv)
{
    SAMPLE *psample = psource->sample;
    VT *pvt = psample->vt;
    ((void (*)(void *, VECTOR *, VECTOR *, float))pvt[5].fn)((char *)psample + pvt[5].delta, ppos, pv, psource->parameter);
}
extern "C" void func_00195368(void *unused, P *p, int sourceCount, SOURCE *sources)
{
    VECTOR vectors[20];
    float ages[10], ends[10];
    EMITTER *pemitter = p->emitter;
    EMITB *pemitb;
    int produced;
    int i;
    if (!pemitter)
        return;
    if (pemitter->dirty)
        OnEmitterValuesChanged(pemitter);
    pemitb = &pemitter->rep->emitb;
    produced = 0;
    for (i = 0; i < sourceCount; i++) {
        SOURCE *psource = &sources[i];
        float amount, random;
        int n;
        if (psource->id == -1)
            continue;
        amount = pemitter->rate * D_002DDED0.dt;
        random = func_0011D448(0.0f, 1.0f);
        n = (int)amount;
        amount -= (float)n;
        if (random < amount)
            n++;
        for (n--; n >= 0; n--) {
            VECTOR pos, v, vScaled;
            VU_FLOAT s;
            float age;
            SampleSource(psource, &pos, &v);
            s = VU_FLOAT(GRand(&pemitb->lmScale));
            VU_VECTOR vs = s * v;
            vScaled.q = vs.q;
            {
                float now = D_002DDED0.t;
                age = now - GRand(&pemitb->lmAge);
            }
            {
                float *pa = ages + produced;
                *pa = age;
            }
            ends[produced] = age + pemitb->life;
            if (pemitb->lmOffset.gMin != pemitb->lmOffset.gMax) {
                VU_VECTOR posOld = pos;
                s = VU_FLOAT(GRand(&pemitb->lmOffset));
                pos.q = AddScaled(posOld, vScaled, s).q;
            }
            {
                VECTOR *pv = vectors + produced;
                pv[0] = pos;
                pv[10] = vScaled;
            }
            produced++;
            if ((unsigned int)produced >= 10)
                goto submit;
        }
    }
submit:
    if (produced > 0) {
        EMITX emitx;
        func_002333B4(&emitx, 0, sizeof(emitx));
        emitx.ppinstance = &pemitter->instance;
        emitx.pemitter = pemitter;
        func_0015B428(pemitter->rep, &emitx, produced, vectors, vectors + 10, ages, ends, 0, 0);
    }
}
