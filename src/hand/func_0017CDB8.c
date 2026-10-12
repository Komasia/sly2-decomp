struct T { char pad[0xF84]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x28]; float g3C; };
float func_001E6648(void *p);
float func_001E6620(void *p);
void func_0017CD00(struct S *p, int n);
void func_0017CDB8(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g3C = func_001E6648(pv); else p->g3C = func_001E6620(pv);
    p->pt->nF8C = p->pt->gF88 < p->g3C;
    func_0017CD00(p, 0);
}
