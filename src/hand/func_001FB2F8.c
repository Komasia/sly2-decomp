typedef int qword __attribute__((mode(TI)));
struct SOURCE;
struct P { char pad[0x1C]; struct SOURCE *source; qword v; };
extern qword D_002A2DD0;
int FFloatsNear(float, float, float) asm("FFloatsNear__Ffff");
void SetDirty__4CSndUiUi(struct P *, unsigned short, unsigned short);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return FFloatsNear(X(a), X(b), 0.0001f) && FFloatsNear(Y(a), Y(b), 0.0001f) && FFloatsNear(Z(a), Z(b), 0.0001f);
}
// name: SafeHouse port (CSnd::SetSource)
void SetSource__4CSndPv(struct P *p, struct SOURCE *source)
{
    p->source = source;
    if (source) SetDirty__4CSndUiUi(p, 0x200, 0x200);
    else if (FNear(D_002A2DD0, p->v)) SetDirty__4CSndUiUi(p, 0x200, 0);
}
