struct T { char pad[0xF84]; void *pF84; float gF88; int nF8C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; float g38; };
float func_001E6648(void *p);
float func_001E6620(void *p);
void func_0017D058(struct S *p, int n);
void func_0017D110(struct S *p, int f) {
    void *pv = p->pt->pF84; if (f) p->g38 = func_001E6648(pv); else p->g38 = func_001E6620(pv);
    p->pt->nF8C = p->pt->gF88 < p->g38;
    func_0017D058(p, 0);
}
