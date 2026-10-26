// func_001A8B50 (wave-4 lane 4) near-miss: aligned 0, 8/365 positional - ONLY the four spill-slot offsets 0x69C0..0x69CC differ.
// Edge/edge and vertex/face contacts between two clipped shapes (ClsgClipSoAllEdges + func_001A81F8, CategorizeAlsg per side,
// func_001A87F0 vertex contacts, then per free segment of side 0 either the func_001A86B8 path (closest points of the two edges via
// func_0011EA60, kind 3) or, when no side-1 segment shares a surface, the nearer endpoint against the farther plane (kind 1)).
// What got it here from w3lane7.v3 (47): Sly-1-style separate local arrays instead of a WORK struct; the second loop indexes
// &aalsg[1][i] (keeps the at+0x20 PRE reaching reg alive => the target's s-register roles and entry schedule); Lilly's
// QwMix(VuFloat(1 - t), a, VuFloat(t), b) for the two lerps (dead 0x6900 stores + vf numbering); Length's float via mtc1.
// Left: the four PRE reaching regs aaipos[0]/aaipos[1]/aaplsg[0]/aaplsg[1] get spill slots in pseudo order = gcse hash-bucket order;
// the target order (6230 < 6430 < 6030 < 6630) needs an expression table of 219 buckets (this file: 169). See build/lane_notes/w4lane4.md.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct SCALAR;
extern "C" SCALAR *func_002564B8(SCALAR *);
struct SCALAR { qword q; SCALAR() { (void)func_002564B8(this); } };
struct VU_VECTOR4 { qword q; VU_VECTOR4(qword a) { q = a; } };
struct SCENE;
struct CONTACT;
struct SPACE { char pad0[0x70]; U position; };
struct EDGE { unsigned short ends[2], surfaces[2]; EDGE *next; int unknown; };
struct SURFACE { U plane; EDGE *first; int tag, flags, unknown; };
struct SHAPE { SPACE *space; void *owner; char pad8[0x8C]; U *vertices; int pad98; SURFACE *surfaces; int edgeCount; EDGE *edges; };
struct NODE { unsigned int left, right; SURFACE *surface; };
struct LSG { U point0, point1, plane0, plane1; float from, to; int flags; SURFACE *surface0, *surface1; EDGE *edge; int side; LSG *next; };
struct XP { char pad0[0x9C]; int kind; void *first, *second; int padA8; XP *next; };
extern "C" {
extern U D_002A2DC0;
int ClipEdges(SCENE *, SHAPE *, SHAPE *, NODE *, int, LSG *) __asm__("ClsgClipSoAllEdges__FP2SOT0P3BSPiP3LSG");
int func_001A81F8(SCENE *, SHAPE *, SHAPE *, int, NODE *, int, LSG *);
void Categorize(int, LSG *, int *, int *, LSG **, LSG **) __asm__("CategorizeAlsg__FiP3LSGPiT2PP3LSGT4");
void func_001A87F0(SCENE *, SHAPE *, SHAPE *, int, int *, LSG **, CONTACT **);
int func_001A86B8(SURFACE *, int, int, LSG *, LSG **);
int func_0011EA60(qword, qword, qword, qword, float *, U *);
void func_001A7C18(SCENE *, SHAPE *, SHAPE *, qword, float, qword, int, void *, void *, CONTACT **);
}

static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

struct VU_FLOAT { qword qw; };
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwMix(VU_FLOAT g1, qword qw1, VU_FLOAT g2, qword qw2)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(qw) : "j"(qw1), "j"(qw2), "j"(g1.qw), "j"(g2.qw));
    return qw;
}
static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(d));
    return f;
}
static inline float PlaneDist(VU_VECTOR4 plane, qword point)
{
    SCALAR dot, one;
    qword r, unit;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane.q), "j"(point));
    dot.q = r;
    one.q = unit;
    float f;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));
    return f;
}
static inline void Closest(qword a, qword b, qword c, qword d, float *parameters, U *normal)
{
    (void)func_0011EA60(a, b, c, d, parameters, normal);
}

extern "C" void func_001A8B50(SCENE *scene, SHAPE *a, SHAPE *b, int nodeCount, NODE *nodes, NODE *last, CONTACT **out)
{
    int aclsg[2];
    LSG aalsg[2][128];
    int acpos[2];
    int aaipos[2][128];
    LSG *aaplsg[2][128];
    LSG *aplsgBoth[2];
    LSG *aplsgPath[32];
    float parameters[2];
    U normal;
    U points[2];
    CONTACT *old = *out;
    aclsg[0] = ClipEdges(scene, b, a, last, 128, aalsg[0]);
    int secondCount = func_001A81F8(scene, a, b, nodeCount, nodes, 128, aalsg[1]);
    aclsg[1] = secondCount;
    if (!aclsg[0] && !secondCount)
        return;
    {
        int i;
        for (i = 0; i < 2; i++)
            Categorize(aclsg[i], aalsg[i], &acpos[i], aaipos[i], aaplsg[i], &aplsgBoth[i]);
    }
    func_001A87F0(scene, a, b, acpos[0], aaipos[0], aaplsg[0], out);
    func_001A87F0(scene, b, a, acpos[1], aaipos[1], aaplsg[1], out);
    for (LSG *segment = aplsgBoth[0]; segment; segment = segment->next) {
        if (!segment->surface0 || !segment->surface1)
            continue;
        int length = func_001A86B8(b->surfaces, segment->surface0 - b->surfaces, segment->surface1 - b->surfaces, aplsgBoth[1], aplsgPath);
        if (length > 0) {
            int j;
            for (j = 0; j < length; j++) {
                LSG *other = aplsgPath[j];
                qword left0 = a->vertices[segment->edge->ends[0]].q, left1 = a->vertices[segment->edge->ends[1]].q;
                qword right0 = b->vertices[other->edge->ends[0]].q, right1 = b->vertices[other->edge->ends[1]].q;
                Closest(left0, left1, right0, right1, parameters, &normal);
                points[0].q = QwMix(VuFloat(1.0f - parameters[0]), left0, VuFloat(parameters[0]), left1);
                points[1].q = QwMix(VuFloat(1.0f - parameters[1]), right0, VuFloat(parameters[1]), right1);
                float distance = -Length(Sub(points[0].q, points[1].q));
                func_001A7C18(scene, a, b, points[0].q, distance, normal.q, 3, segment->edge, other->edge, out);
            }
            continue;
        }
        int i;
        for (i = 0; i < aclsg[1]; i++) {
            LSG *other = &aalsg[1][i];
            if (other->surface0 == a->surfaces + segment->edge->surfaces[0] || other->surface0 == a->surfaces + segment->edge->surfaces[1] ||
                other->surface1 == a->surfaces + segment->edge->surfaces[0] || other->surface1 == a->surfaces + segment->edge->surfaces[1])
                goto next;
        }
        {
            float firstDistance = PlaneDist(segment->plane0.q, a->space->position.q);
            float secondDistance = PlaneDist(segment->plane1.q, a->space->position.q);
            SURFACE *surface;
            int endpoint;
            if (secondDistance < firstDistance) {
                endpoint = 1 - segment->side;
                surface = segment->surface0;
            } else {
                endpoint = segment->side;
                surface = segment->surface1;
            }
            U *point = a->vertices + segment->edge->ends[endpoint];
            XP *contact = (XP *)*out;
            while (contact) {
                if (contact->kind == 1 && contact->first == point && contact->second == surface)
                    break;
                contact = contact->next;
            }
            if (contact)
                continue;
            qword position = point->q, plane = surface->plane.q;
            float distance = PlaneDist(plane, position);
            func_001A7C18(scene, a, b, position, distance, plane, 1, point, surface, out);
        }
    next:;
    }
    if (old == *out && (!aclsg[0] || !aclsg[1]))
        func_001A7C18(scene, a, b, a->space->position.q, 0.0f, D_002A2DC0.q, 13, 0, 0, out);
}
