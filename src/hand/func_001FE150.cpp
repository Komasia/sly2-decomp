struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[8]; };
struct X { char pad[0xC]; VT *pvt; };
struct Ref;
extern "C" void func_00259BB0(Ref *, X *);
extern "C" void func_00259B48(Ref *, X *);
struct Ref {
    X *px;
    Ref(X *p) { func_00259BB0(this, p); }
    Ref(const Ref &r) { func_00259BB0(this, r.px); }
    Ref &operator=(const Ref &r) { func_00259B48(this, r.px); return *this; }
    Ref &operator=(X *p) { func_00259B48(this, p); return *this; }
    ~Ref() { if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d); }
};
struct S { int c; Ref a[8]; };
struct P { char pad[0x204]; S s; };
extern int D_002DD5BC;
extern int D_002F7900;
extern int D_002E1E40;
extern "C" {
Ref RefTakeMusic(P *, int) asm("RefTakeMusic__FP8SOUNDMGRi");
void Stop(X *, float) asm("Stop__4CSndf");
X *PstreamFindMusic(P *, int) asm("PstreamFindMusic__FP8SOUNDMGRi");
X *PsndNewVoice(X *, int) asm("PsndNewVoice__FP9SNDSTREAMPv");
void AddVoiceFalloff(X *, int, int, float, float *) asm("AddVoiceFalloff__9CSndVoiceiiPvf");
}
struct V2 { float x, y; };
static inline void Set(V2 *pv, float x, float y) { pv->x = x; pv->y = y; }
// name: SafeHouse port (PsndPushMusic)
extern "C" X *PsndPushMusic__FP8SOUNDMGRi(P *p, int n)
{
    Ref r = RefTakeMusic(p, n);
    X *top = p->s.c > 0 ? (p->s.a + p->s.c - 1)->px : 0;
    if (top) Stop(top, 0.0f);
    if (r.px) {
        r.px->pvt->a[7].pfn((char *)r.px + r.px->pvt->a[7].d);
    } else {
        X *v = PstreamFindMusic(p, n);
        if (!v || p->s.c == 8) return 0;
        float f = 1.0f;
        r = PsndNewVoice(v, 4);
        V2 af;
        Set(&af, 2000.0f, 5000.0f);
        AddVoiceFalloff(r.px, 3, D_002DD5BC, f, &af.x);
        AddVoiceFalloff(r.px, 3, D_002F7900, f, &af.x);
        AddVoiceFalloff(r.px, 4, D_002E1E40, f, &af.x);
    }
    return (p->s.a[p->s.c++] = r).px;
}
