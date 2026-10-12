typedef struct CRef { int m_tagk; float m_g; } CRef;
extern char D_003D4A60[];
struct X { char pad[0xA8]; float *pg; };
extern struct X *D_003E0F9C;
struct S { int pad[2]; void *p8; void *pC; void *p10; };
void func_002581C0(CRef *pref, void *p, void *q);
void func_00129EC8(CRef *pref);
float func_00154C90(struct S *p)
{
    float g;
    if (D_003E0F9C) {
        g = *D_003E0F9C->pg;
    } else if (p->p8 && p->pC && p->p10) {
        CRef ref;
        float g2, g3;
        func_002581C0(&ref, p->p8, D_003D4A60);
        g = ref.m_g;
        func_00129EC8(&ref);
        func_002581C0(&ref, p->pC, D_003D4A60);
        g2 = ref.m_g;
        func_00129EC8(&ref);
        func_002581C0(&ref, p->p10, D_003D4A60);
        g3 = ref.m_g;
        func_00129EC8(&ref);
        g = (g + g2 + g3) / 3.0f;
    } else {
        g = 0.0f;
    }
    return g;
}
