typedef int qword __attribute__((mode(TI)));
struct SCALAR;
struct VECTOR;
extern "C" SCALAR *func_002564B8(SCALAR *);
extern "C" VECTOR *func_002564C0(VECTOR *);
struct SCALAR { qword q; SCALAR() { (void)func_002564B8(this); } };
struct VECTOR { qword q; VECTOR() { (void)func_002564C0(this); } };
struct W;
struct B;
struct XP;
struct POINTS { int count; qword *data; };
struct A { char pad[0x90]; POINTS points; };
struct SURFACE { qword plane; char pad10[8]; int flags; };
struct EDGE { unsigned short ends[2]; };
struct NODE { char pad[0x10]; qword point; char pad20[0x50 - 0x20]; SURFACE *surface; EDGE *edge; int reverse; NODE *next; };
extern "C" {
extern float D_002A6AD0;
void func_001A7C18(W *, A *, B *, qword, qword, int, int, int, XP **, float);
}

/* signed distance of pos from plane: dot(plane.xyz, pos.xyz) - plane.w, via VU0 macro mode */
static inline float PlaneDist(qword plane, qword pos)
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w" : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q));
    return f;
}

extern "C" void func_001A87F0(W *w, A *a, B *b, int count, int *indices, NODE **heads, XP **out)
{
    float d;
    NODE *m;
    for (int i = 0; i < count; i++) {
        POINTS *positions = &a->points;
        qword *data = positions->data;
        int index = indices[i];
        NODE *head = heads[i];
        SURFACE *best = 0;
        float bestMin = D_002A6AD0;
        float bestOrig;
        qword bestNormal;
        qword position = data[index];
        NODE *n;
        for (n = head; n; n = n->next) {
            SURFACE *s = n->surface;
            if (!(s->flags & 8)) {
                qword plane = s->plane;
                s->flags |= 8;
                float orig = PlaneDist(plane, position);
                float min = orig;
                for (m = head; m; m = m->next) {
                    d = PlaneDist(plane, data[m->edge->ends[1 - m->reverse]]);
                    if (d < min) min = d;
                }
                if (bestMin < min) { bestNormal = plane; best = s; bestMin = min; bestOrig = orig; }
            }
        }
        for (n = head; n; n = n->next) n->surface->flags &= ~8;
        VECTOR normal;
        normal.q = bestNormal;
        func_001A7C18(w, a, b, position, normal.q, 1, (int)&a->points.data[index], (int)best, out, bestOrig);
        for (m = head; m; m = m->next) {
            d = PlaneDist(bestNormal, m->point);
            if (d < bestOrig) {
                qword pt = m->point;
                VECTOR nn;
                nn.q = bestNormal;
                func_001A7C18(w, a, b, pt, nn.q, 2, (int)m->edge, (int)best, out, d);
            }
        }
    }
}
