#define FIELD_OFFSET(t,m) ((uint)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U { qword q; float f[4]; U() __asm__("func_002564B8"); };
typedef union { qword q[2]; uint a[8]; } MASK;
typedef struct NODE { qword plane; struct NODE *left, *right; int leftLeaf, rightLeaf; } NODE;
struct SPHERE { U position; float bias, weight; float Score(qword pos); };
typedef struct OBJ { char pad[0x100]; SPHERE sphere; } OBJ;
typedef struct { float score; OBJ *object; } RESULT;
typedef struct {
    char pad[0x4154]; OBJ *objects[256]; int dirty, treeCount;
    NODE *tree; int leafCount; MASK *leaves; int p4568, p456C; MASK mask;
} WORLD;
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char MASK_Size[sizeof(MASK)==32?1:-1];
typedef char NODE_Size[sizeof(NODE)==32?1:-1];
typedef char SPHERE_Size[sizeof(SPHERE)==32?1:-1];
typedef char RESULT_Size[sizeof(RESULT)==8?1:-1];
typedef char WORLD_objects_Offset[FIELD_OFFSET(WORLD,objects)==16724?1:-1];
typedef char WORLD_dirty_Offset[FIELD_OFFSET(WORLD,dirty)==17748?1:-1];
typedef char WORLD_treeCount_Offset[FIELD_OFFSET(WORLD,treeCount)==17752?1:-1];
typedef char WORLD_tree_Offset[FIELD_OFFSET(WORLD,tree)==17756?1:-1];
typedef char WORLD_leafCount_Offset[FIELD_OFFSET(WORLD,leafCount)==17760?1:-1];
typedef char WORLD_leaves_Offset[FIELD_OFFSET(WORLD,leaves)==17764?1:-1];
typedef char WORLD_mask_Offset[FIELD_OFFSET(WORLD,mask)==17776?1:-1];
typedef char NODE_plane_Offset[FIELD_OFFSET(NODE,plane)==0?1:-1];
typedef char NODE_left_Offset[FIELD_OFFSET(NODE,left)==16?1:-1];
typedef char NODE_right_Offset[FIELD_OFFSET(NODE,right)==20?1:-1];
typedef char NODE_leftLeaf_Offset[FIELD_OFFSET(NODE,leftLeaf)==24?1:-1];
typedef char NODE_rightLeaf_Offset[FIELD_OFFSET(NODE,rightLeaf)==28?1:-1];
typedef char OBJ_sphere_Offset[FIELD_OFFSET(OBJ,sphere)==256?1:-1];
typedef char SPHERE_position_Offset[FIELD_OFFSET(SPHERE,position)==0?1:-1];
typedef char SPHERE_bias_Offset[FIELD_OFFSET(SPHERE,bias)==16?1:-1];
typedef char SPHERE_weight_Offset[FIELD_OFFSET(SPHERE,weight)==20?1:-1];
typedef char RESULT_score_Offset[FIELD_OFFSET(RESULT,score)==0?1:-1];
typedef char RESULT_object_Offset[FIELD_OFFSET(RESULT,object)==4?1:-1];
extern "C" void *func_002333B4(void *, int, uint);
extern "C" void *func_002564B8(void *);
static inline float PlaneDistance(qword plane, qword pos)
{
    U d, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%0,%4\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w\n\tqmfc2.ni %2,%0"
        : "=j"(r), "=&j"(unit), "=r"(f) : "0"(plane), "j"(pos));
    one.q = unit;
    d.q = r;
    return f;
}
static inline float Length(qword a, qword b)
{
    qword r, one;
    float f;
    __asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(r),"=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(r));
    __asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));
    return f;
}
inline float SPHERE::Score(qword pos) { return bias + weight * Length(pos,position.q); }
static inline int BitIndex(uint isolated, int base)
{
    int result = base;
    if (isolated & 0xAAAAAAAAU) result++;
    if (isolated & 0xCCCCCCCCU) result += 2;
    if (isolated & 0xF0F0F0F0U) result += 4;
    if (isolated & 0xFF00FF00U) result += 8;
    if (isolated & 0xFFFF0000U) result += 16;
    return result;
}
extern "C" void func_001A3F78(WORLD *p, qword pos, int capacity, RESULT *results)
{
    MASK mask;
    NODE *n;
    MASK *leaf;
    uint i;
    func_002333B4(results, 0, capacity * sizeof(RESULT));
    mask.q[0] = p->mask.q[0];
    mask.q[1] = p->mask.q[1];
    if (p->tree) {
        n = p->tree;
        do {
            if (PlaneDistance(n->plane, pos) < 0.0f) {
                if (n->left) n = n->left;
                else { leaf = &p->leaves[n->leftLeaf]; break; }
            } else {
                if (n->right) n = n->right;
                else { leaf = &p->leaves[n->rightLeaf]; break; }
            }
        } while (n);
        for (i = 0; i < 8; i++) mask.a[i] |= leaf->a[i];
    }
    for (i = 0; i < 8; i++) {
        uint word = mask.a[i];
        if (word) {
            do {
                uint remaining = word & (word - 1);
                uint isolated = word & ~remaining;
                OBJ *o = p->objects[BitIndex(isolated, i * 32)];
                float score = o->sphere.Score(pos);
                int j = capacity;
                while (j > 0) {
                    if (score < results[j - 1].score) break;
                    if (j < capacity) results[j] = results[j - 1];
                    j--;
                }
                if (j < capacity) { results[j].score = score; results[j].object = o; }
                word = remaining;
            } while (word);
        }
    }
}
