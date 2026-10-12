/* WIP 13/97: inline Send(CRef ref) + Fn(const CRef&) fixes s-regs and stack slots; remaining: target loads D_003E0FE4 (this) into s0 BEFORE the copy-ctor call (ours loads after) and keeps &copy as sp+0x10 constant. */
class CRef;
extern "C" void func_00129EC8(CRef *pref);
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(bool f) { m_tagk = 0x17; m_tag = f; }
    CRef(const CRef &ref) asm("func_001291A8");
    ~CRef() { func_00129EC8(this); }
};
class O { public: CRef Fn(const CRef &ref, void *p) asm("func_00258200"); };
struct S { char pad[0x40]; int x40; int x44, x48; int x4C; };
extern "C" {
extern char D_003DA530[], D_003D9ED0[], D_003D4A60[], D_002E65E0[];
extern O *D_003E0FE4;
int func_001D9880(void *p);
int func_001B0160(void *p);
void func_001ACBB8(S *s);
void func_001ACC38(S *s, int n);
void func_001AF660(void *p);
void func_001DDB08(void *p);
int func_001B0108(void *p);
void func_001AF608(void *p);
void func_001ACB58(S *s, int n);
void func_001ABD40(void *p);
void func_001ACFE0(S *s);
}
static inline void Send(CRef ref) { D_003E0FE4->Fn(ref, D_003D4A60); }
void func_001ACFE0(S *s)
{
    switch (s->x40) {
    case 17: case 18: case 21: case 24:
        {
            void *g = D_003DA530;
            if (func_001D9880(g) && func_001B0160(D_003D9ED0)) {
                func_001ACBB8(s);
                func_001ACC38(s, 2);
                func_001AF660(D_003D9ED0);
                func_001DDB08(g);
                break;
            }
        }
        /* fallthrough */
    case 20: case 23: case 29: case 35: case 36: case 46:
        func_001ACBB8(s);
        func_001ACC38(s, 2);
        if (func_001B0108(D_003D9ED0))
            func_001AF608(D_003D9ED0);
        break;
    case 27: case 28: case 32:
        func_001ACBB8(s);
        break;
    case 34:
        {
            CRef ref(true);
            Send(ref);
        }
        if (s->x4C < 4) {
            if (s->x4C > 0) {
                func_001ACB58(s, 0x1A);
                func_001ABD40(D_002E65E0);
            }
        }
        break;
    }
}
