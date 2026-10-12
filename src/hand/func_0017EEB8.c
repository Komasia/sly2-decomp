struct O { char pad[0xE4]; int nE4; };
struct S { char pad[0x30]; struct O *p30; int n34; float g38; };
extern float D_002BE7B8;
float func_001E6648(struct O *p);
float func_001E6620(struct O *p);
int func_0017EEB8(struct S *p) {
    float g;
    if (p->p30->nE4) return 0;
    if (p->n34) g = func_001E6648(p->p30); else g = func_001E6620(p->p30);
    if (D_002BE7B8 < __builtin_fabsf(p->g38 - g)) return 0;
    return 1;
}
