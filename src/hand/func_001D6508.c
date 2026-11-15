/* Find or make the render tree entry for a sphere (pos, sRadius) with draw distance sMax and channel mask grfChannels.
 * Starting at the world's root block (+0x3E5C), each level (a chain of 4-entry blocks linked through the last
 * entry's pblockNext) is searched for the node entry (kind 1) whose sphere contains this one, whose draw distance
 * covers it (1e10 = unlimited) and whose channels include the mask; the best (smallest r * min(sMax, 1e5)^2) node
 * is descended into. When no node fits, a free entry (kind -1) of the level is used, or a new block is chained on;
 * it gets the sphere, sMax and mask and is returned (the caller sets its kind). */
typedef int qword __attribute__((mode(TI)));

#define KIND_FREE -1
#define KIND_NODE 1

struct BLOCK;
struct RENDER {
    /* 0x00 */ union { qword q; struct { float x, y, z, r; } s; } sphere;
    /* 0x10 */ float sMax;            /* draw distance, 1e10 = unlimited */
    /* 0x14 */ long kind : 4;
    long channels : 8;
    /* 0x18 */ struct BLOCK *pblockChild;
    /* 0x1c */ struct BLOCK *pblockNext;
};
struct BLOCK { struct RENDER arender[4]; };
extern float D_002A7870;              /* the starting best score (a large value) */
typedef struct { char pad[0x3E5C]; struct BLOCK *pblockRoot; } SW;
struct BLOCK *func_001D6480(SW *psw);
static inline float Min(float a, float b) { return b < a ? b : a; }
static inline float Dist(qword a, qword b)
{
    qword d, t, va;
    float f;
    __asm__("qmtc2.ni %1, %0" : "=j"(va) : "r"(a));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(va), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d), "=&j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
struct RENDER *func_001D6508(SW *psw, qword pos, float sRadius, float sMax, int grfChannels)
{
    struct BLOCK *pblockLevel = psw->pblockRoot;
    struct BLOCK *pblock;
    struct BLOCK *pblockChild;
    struct RENDER *prenderFree;
    float best;
    if (!pblockLevel)
        return 0;
    for (;;) {
        pblock = pblockLevel;
        best = D_002A7870;
        pblockChild = 0;
        prenderFree = 0;
        for (;;) {
            struct BLOCK *pblockNext = pblock->arender[3].pblockNext;
            unsigned int irender;
            for (irender = 0; irender < 4; irender++) {
                struct RENDER *prender = &pblock->arender[irender];
                int kind = prender->kind;
                if (kind != KIND_FREE) {
                    if (kind == KIND_NODE) {
                        float dist = Dist(pos, prender->sphere.q), sMaxNode;
                        if (dist + sRadius <= prender->sphere.s.r) {
                            sMaxNode = prender->sMax;
                            if (sMaxNode == 1e10f || dist + sMax <= sMaxNode) {
                                if (!(grfChannels & ~prender->channels)) {
                                    float score = prender->sphere.s.r * Min(sMaxNode, 100000.0f) * Min(sMaxNode, 100000.0f);
                                    if (score < best) {
                                        best = score;
                                        pblockChild = prender->pblockChild;
                                    }
                                }
                            }
                        }
                    }
                } else if (!prenderFree) {
                    prenderFree = prender;
                }
            }
            if (!pblockNext)
                break;
            pblock = pblockNext;
        }
        if (!pblockChild) {
            if (!prenderFree) {
                pblock->arender[3].pblockNext = func_001D6480(psw);
                prenderFree = pblock->arender[3].pblockNext->arender;
            }
            prenderFree->sMax = sMax;
            prenderFree->sphere.q = pos;
            prenderFree->sphere.s.r = sRadius;
            prenderFree->channels = grfChannels;
            break;
        }
        pblockLevel = pblockChild;
    }
    return prenderFree;
}
