typedef int qword __attribute__((mode(TI)));
struct P { char pad[0x1C]; int n1C; qword v; };
extern qword D_002A2DD0;
int FFloatsNear(float, float, float) asm("FFloatsNear__Ffff");
void SetDirty__4CSndUiUi(struct P *, int, int);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return FFloatsNear(X(a), X(b), 0.0001f) && FFloatsNear(Y(a), Y(b), 0.0001f) && FFloatsNear(Z(a), Z(b), 0.0001f);
}
// name: SafeHouse port (CSnd::SetPosition)
void SetPosition__4CSndG9VU_VECTOR(struct P *p, qword v)
{
    p->v = v;
    if (!FNear(D_002A2DD0, v)) SetDirty__4CSndUiUi(p, 0x200, 0x200);
    else if (!p->n1C) SetDirty__4CSndUiUi(p, 0x200, 0);
}
