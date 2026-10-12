struct O { char pad[0x70]; long fl; };
struct P { char pad[0xEC]; struct O *po; };
struct S { int a; struct P *pp; char pad[8]; long fl; };
int func_0020FA10(struct O *po, struct S *p) {
    int r = 0;
    if (!(p->fl & 0x1000000000000L)) {
        struct O *o = p->pp->po;
        if (!(o->fl & 4)) r = o != po;
    }
    return r;
}
