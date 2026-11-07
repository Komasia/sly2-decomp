struct R { char pad[0x14]; int n14; int pad2; float g1C; float g20; };
struct P { char pad[0x20]; void *p20; void *p24; };
struct R *PctrlFindXfh__FP7XFBASICiii(struct P *, int, int, int);
void func_0012DCA0(void *, void *, int, int, float, float);
void func_001F8B58(struct P *p, int n, int m, float f, float g)
{
    struct R *r = PctrlFindXfh__FP7XFBASICiii(p, 4, n, m);
    if (r) {
        r->n14 = n;
        r->g1C = f;
        r->g20 = g;
    } else if (n != -1) {
        func_0012DCA0(p->p20, p->p24, m, n, f, g);
    }
}
