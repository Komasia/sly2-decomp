// (Claude agent) matched: the CRef copy ctor (__4CRefRC4CRef) must be declared returning this, not void.
extern "C" {
void Decref(void *p) asm("Decref__4CRef");
void *func_001291A8(void *p, const void *q); /* CRef copy ctor: returns this */
extern void *D_003E0FD8;
extern int D_002C2D8C;
void ApplyVibrationSetting(void) asm("ApplyVibrationSetting__Fv");
}
struct RAW { int m_tagk; int m_tag; };
static inline void SetBool(RAW *p, int f) { p->m_tagk = 0x17; p->m_tag = f; }
static inline void SetBool2(RAW *p, int f) { p->m_tag = f; p->m_tagk = 0x17; }
struct CRef {
    int m_tagk; int m_tag;
    CRef() {}
    CRef(int f) { m_tagk = 0x17; m_tag = f; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    CRef(const RAW &r) { func_001291A8(this, &r); }
    ~CRef() { Decref(this); }
};
extern char D_003D4A60[];
extern "C" CRef func_00258200(void *pv, const CRef &ref, void *p);
static inline void SetPv(void *pv, const RAW &r, void *)
{
    CRef arg(r);
    const CRef &ret = func_00258200(pv, arg, D_003D4A60);
}
static inline void SetPv2(void *pv, const RAW &r)
{
    CRef arg(r);
    const CRef &ret = func_00258200(pv, arg, D_003D4A60);
}
// name: SafeHouse port (ApplyVibrationSetting)
void ApplyVibrationSetting(void)
{
    RAW ref;
    switch (D_002C2D8C) {
    case 1: break;
    case 2: { void *pv = D_003E0FD8; ref.m_tagk = 0x17; ref.m_tag = 0; SetPv(pv, ref, D_003D4A60); } Decref(&ref); break;
    case 3: { void *pv = D_003E0FD8; SetBool2(&ref, 1); SetPv2(pv, ref); } Decref(&ref); break;
    }
}
