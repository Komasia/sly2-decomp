/* ApplyVibrationSetting (SafeHouse rumble.h, orig 0x1D54B8): write the vibration option into the saved progress
 * record before it is saved: option On (2) stores fNoVibration = false, Off (3) stores true; 1 (title shown, record
 * decides) leaves it. Matching note: the CRef copy ctor (__4CRefRC4CRef) must be declared returning this, not void. */
extern "C" {
void Decref(void *p) asm("Decref__4CRef");
void *func_001291A8(void *p, const void *q); /* CRef copy ctor: returns this */
extern void *D_003E0FD8;   /* the progress record */
extern int D_002C2D8C;     /* the vibration option (SafeHouse g_vibrationSetting) */
void ApplyVibrationSetting(void) asm("ApplyVibrationSetting__Fv");
}
#define TAGK_Bool 0x17
#define VIBRATION_On 2
#define VIBRATION_Off 3
struct RAW { int m_tagk; int m_tag; };
static inline void SetBool(RAW *p, int f) { p->m_tagk = TAGK_Bool; p->m_tag = f; }
static inline void SetBool2(RAW *p, int f) { p->m_tag = f; p->m_tagk = TAGK_Bool; }
struct CRef {
    int m_tagk; int m_tag;
    CRef() {}
    CRef(int f) { m_tagk = TAGK_Bool; m_tag = f; }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    CRef(const RAW &r) { func_001291A8(this, &r); }
    ~CRef() { Decref(this); }
};
extern char D_003D4A60[];   /* the progress key of the fNoVibration flag */
extern "C" CRef func_00258200(void *pv, const CRef &ref, void *p);   /* set a progress value */
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
    case VIBRATION_On: { void *pv = D_003E0FD8; ref.m_tagk = TAGK_Bool; ref.m_tag = 0; SetPv(pv, ref, D_003D4A60); } Decref(&ref); break;
    case VIBRATION_Off: { void *pv = D_003E0FD8; SetBool2(&ref, 1); SetPv2(pv, ref); } Decref(&ref); break;
    }
}
