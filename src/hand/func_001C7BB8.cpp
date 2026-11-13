extern "C" {
void __10STACKSCOPE(void *p);
void _$_10STACKSCOPE(void *p, int n);
void Decref(void *p) asm("Decref__4CRef");
void *func_001C7B18(void *p);
}
class FRAME { int a[4]; public: FRAME() { __10STACKSCOPE(this); } ~FRAME() { _$_10STACKSCOPE(this, 2); } };
struct CRef { int m_tagk; int m_tag; };
extern char D_003D4A60[];
extern "C" void NProgress(CRef *pref, void *pv, void *p);
static inline int NFromPv(void *pv) { CRef ref; int n; NProgress(&ref, pv, D_003D4A60); n = ref.m_tag; Decref(&ref); return n; }
extern "C" int func_001C7BB8(void *p);
int func_001C7BB8(void *p)
{
    FRAME frame;
    void *pv = func_001C7B18(p);
    if (!pv) return 0;
    return NFromPv(pv);
}
