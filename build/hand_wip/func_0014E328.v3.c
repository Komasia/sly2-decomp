/* v3 (Claude agent, lane D6): aligned 5 -> 3. One commented register pin (p in s1) plus memmove args from a pointer local pe = &p->ae[i], (pe + 1, pe). Left: target forms A = i*16 + p, copies it to a1, then +0x320 / +0x310; ours forms pe = p + (i*16 + 0x310) and a0 = pe + 0x10. */
/* v2 (Claude agent, 2026-10-17): vt[4] call takes (po, b) [fixes b in s5]; i=0 in the for; &p->ae[i+1] args -> aligned 5. Left: memmove args, target forms (p + i*16) once then +0x320/+0x310. */
struct VTE { short d; short pad; void (*pfn)(void *, ...); };
struct O { int pad[3]; struct VTE *vt; };
struct E { int prio; struct O *po; int a; int b; };
struct P { char pad[0x30C]; int c; struct E ae[8]; char pad2[0x390 - 0x390]; float t; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
void *func_002332B8(void *dst, void *src, int cb);
void func_0014E328(struct P *p0, int prio, struct O *po, int a, int b)
{
    register struct P *p asm("$17") = p0; /* register pin: the target keeps p in s1 (i in s2) */
    int i;
    if (p->c < sizeof(p->ae) / sizeof(p->ae[0])) {
        for (i = 0; i < p->c; i++) {
            if (p->ae[i].prio < prio)
                break;
        }
        {
            struct E *pe = &p->ae[i];
            func_002332B8(pe + 1, pe, (p->c - i) * sizeof(struct E));
        }
        p->ae[i].prio = prio;
        p->ae[i].po = po;
        p->ae[i].a = a;
        p->ae[i].b = b;
        p->c++;
        {
            struct VTE *e = &po->vt[4];
            ((void (*)(void *, int))e->pfn)((char *)po + e->d, b);
        }
        if (i == 0) {
            if (p->c >= 2) {
                struct O *o = p->ae[1].po;
                struct VTE *e = &o->vt[3];
                ((void (*)(void *, int, int))e->pfn)((char *)o + e->d, p->ae[1].a, p->ae[1].b);
            }
            p->t = D_002DDED0.t;
            {
                struct VTE *e = &po->vt[2];
                ((void (*)(void *, int, int))e->pfn)((char *)po + e->d, a, b);
            }
        }
    }
}
