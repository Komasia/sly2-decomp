/* WIP 101/107: cond Eval directly in the if (no inline) puts T at sp+0x10 and &t in s5 like the target, but the second Eval temp then gets sp+0x20 (target reuses sp+0); also s-reg assignment and v?v:x3B28 (beqz/b vs beql). */
struct CRef;
extern "C" void func_00129EC8(CRef *);
struct CRef { int m_tagk; union { float g; int n; } m_tag; CRef(const CRef &) __asm__("func_001291A8"); ~CRef() { func_00129EC8(this); } };
struct GD { char pad[0x3A18]; char x3A18[0x3B1C - 0x3A18]; int x3B1C; int pad2[2]; int x3B28; };
struct B { char data[0x5464]; };
struct T;
extern "C" void func_001AE4A0(T *, int);
struct T { char data[0x10]; T() __asm__("func_001AE478"); ~T() { func_001AE4A0(this, 2); } };
extern "C" {
extern struct GD D_003DD490;
extern struct B D_002E6604[];
extern char D_003D9ED0[], D_002A6EE0[], D_002A6EC8[];
char *func_0013E368(void *p, int n);
char *func_0021ED58(char *d, const char *s);
int func_001B0078(void *g);
int func_001D89A8(void *p, int n);
int func_001DDD40(int n);
char *func_001D82B8(void *p, void *q);
void func_0021ECD8(char *buf, char *fmt, ...);
}
CRef Eval(int a, void *b) __asm__("func_002581C0");
static inline float GetF(int x, void *pb) { CRef r = Eval(x, pb); return r.m_tag.g; }
static inline int GetN(int x, void *pb) { return Eval(x, pb).m_tag.n; }
static inline void Fmt(char *buf, B *pb)
{
        T t;
        int v = func_001D89A8(D_002A6EE0, 0);
        int tag = GetN(v ? v : D_003DD490.x3B28, pb);
        char *a = func_0013E368(&D_003DD490, func_001DDD40(tag));
        func_0021ECD8(buf, D_002A6EC8, a, func_001D82B8(D_003DD490.x3A18, pb));
}
extern "C" void func_001ADC40(char *buf, int idx)
{
    struct B *pb = &D_002E6604[idx];
    if (Eval(D_003DD490.x3B1C, pb).m_tag.g != 0.0f) {
        T t;
        int v = func_001D89A8(D_002A6EE0, 0);
        int tag = GetN(v ? v : D_003DD490.x3B28, pb);
        char *a = func_0013E368(&D_003DD490, func_001DDD40(tag));
        func_0021ECD8(buf, D_002A6EC8, a, func_001D82B8(D_003DD490.x3A18, pb));
    } else {
        switch (func_001B0078(D_003D9ED0)) {
        case 0x1E:
        case 0x1F:
            func_0021ED58(buf, func_0013E368(&D_003DD490, 0x44));
            break;
        case 0x19:
            func_0021ED58(buf, func_0013E368(&D_003DD490, 0x45));
            break;
        }
    }
}
