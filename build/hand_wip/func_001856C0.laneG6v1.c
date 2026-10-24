/* laneG6v1 (Claude agent): fresh clean rewrite (no pins, no mul.s/lw instruction asms), aligned 104 (old .c 106 used mul.s asms). Structure and call contracts match. Left: i lives in a2 (target s3, with next=i+1 spilled to 0xD0 and stored twice, i*2 spilled to 0xD4 and +i done inside the edge loop); ours hoists 3i and keeps out/mesh in s7/s4. A plain `next` local (i = next) makes the frame 0x10 bigger (102 aligned but worse layout). */
typedef int qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; } U;
typedef struct M4 { U r[4]; } M4;
typedef struct VTE { short delta, pad; void *fn; } VTE;
typedef struct I3 { int index[3]; } I3;
typedef struct MESH { char pad0[0xC]; VTE *vt; char pad10[0xD4]; qword *vertices; int count; I3 *triangles; I3 *neighbors; } MESH;
typedef struct LIST { int count; int pad[3]; qword planes[1]; } LIST;
typedef struct PARAMS { float a, b, duration; } PARAMS;
extern float D_002DDED4, D_002A5688;
extern void func_0011EE08(qword, qword, qword, qword *, float *, float *);
extern float func_0011D018(float, float, float, PARAMS *, float *);
extern void func_001193C0(qword *, qword, float);
static inline qword Transform(M4 *m, qword p)
{
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddaz.xyz $ACC, %3, %0z\n\tvmaddw.xyz %0, %4, $vf0w"
        : "+j"(p) : "j"(m->r[0].q), "j"(m->r[1].q), "j"(m->r[2].q), "j"(m->r[3].q));
    return p;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Normalize(qword a)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(a), "j"(d));
    return r;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
void func_001856C0(MESH *mesh, LIST *out, int count, qword *points, PARAMS *params, float radius)
{
    M4 mat;
    U v[3];
    U closest;
    U plane;
    float dist, clamped;
    int i, edge, n;
    M4 *pm;
    VTE *e = &mesh->vt[31];
    float stop, step;
    pm = ((M4 *(*)(void *))e->fn)((char *)mesh + e->delta);
    mat = *pm;
    stop = params->duration * ((params->a + params->b) * 0.5f);
    step = D_002DDED4 * 0.5f;
    for (i = 0; i < mesh->count; i++) {
        I3 *t = &mesh->triangles[i];
        I3 *nb = &mesh->neighbors[i];
        qword normal;
        if (nb->index[0] != -1 && nb->index[1] != -1 && nb->index[2] != -1) continue;
        v[0].q = Transform(&mat, mesh->vertices[t->index[0]]);
        v[1].q = Transform(&mat, mesh->vertices[t->index[1]]);
        v[2].q = Transform(&mat, mesh->vertices[t->index[2]]);
        normal = Cross(Sub(v[1].q, v[0].q), Sub(v[2].q, v[0].q));
        for (edge = 0; edge < 3; edge++) {
            qword start, end, best_plane;
            float best;
            qword *pp;
            if (((int *)mesh->neighbors)[i * 3 + edge] != -1) continue;
            start = v[(edge + 1) % 3].q;
            end = v[(edge + 2) % 3].q;
            best = D_002A5688;
            for (n = count, pp = points; n > 0; n--, pp++) {
                qword edge_plane = Cross(normal, Sub(end, start));
                qword point = *pp;
                func_0011EE08(point, start, end, &closest.q, 0, &dist);
                if (dist < radius + stop) {
                    qword unit = Normalize(edge_plane);
                    func_0011D018(radius, Dot(unit, Sub(point, closest.q)), step, params, &clamped);
                    if (clamped < best) {
                        best = clamped;
                        func_001193C0(&plane.q, unit, best);
                        best_plane = plane.q;
                    }
                }
            }
            if (best != D_002A5688) out->planes[out->count++] = best_plane;
        }
    }
}
