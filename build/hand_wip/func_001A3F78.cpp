#define FIELD_OFFSET(t,m) ((uint)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U {qword q;float f[4];U();};
typedef union {qword q[2];uint a[8];} MASK;
struct HOME{qword q;};struct WORK{MASK mask;HOME distance,unity;};
inline void*operator new(unsigned,void*destination){return destination;}
typedef struct NODE { qword plane; struct NODE *left, *right; int leftLeaf, rightLeaf; } NODE;
struct SPHERE { U position; float bias, weight; float Score(qword pos); };
typedef struct OBJ { char pad[0x100]; SPHERE sphere; } OBJ;
typedef struct { float score; OBJ *object; } RESULT;
typedef struct {
    char pad[0x4154]; OBJ *objects[256]; int word4554, word4558;
    NODE *tree; int word4560; MASK *leaves; int word4568, word456C; MASK mask;
} WORLD;
extern "C" void *func_002333B4(void *, int, uint);
extern "C" U*func_002564B8(U*);
inline U::U(){(void)func_002564B8(this);}
static inline float PlaneDistance(HOME*first,HOME*second,qword plane,qword pos)
{
    U*d=new((void*)first)U;U*one=new((void*)second)U;
    qword r, unit;
    int word;register float f __asm__("$f2");
    __asm__("vmul.xyz %0,%0,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w"
        : "=j"(r),"=&j"(unit):"0"(plane),"j"(pos));
    d->q=r;
    __asm__("qmfc2.ni %0,%2\n\tmtc1 %0,%1":"=&r"(word),"=f"(f):"j"(d->q));
    one->q=unit;
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
    int result=base+1;
    if(!(isolated&0xAAAAAAAAU))result=base;
    if (isolated & 0xCCCCCCCCU) result += 2;
    if (isolated & 0xF0F0F0F0U) result += 4;
    if (isolated & 0xFF00FF00U) result += 8;
    if (isolated & 0xFFFF0000U) result += 16;
    return result;
}
typedef char Offset_0[FIELD_OFFSET(U,q)==0?1:-1];
typedef char Offset_1[FIELD_OFFSET(U,f)==0?1:-1];
typedef char Offset_2[FIELD_OFFSET(HOME,q)==0?1:-1];
typedef char Offset_3[FIELD_OFFSET(WORK,mask)==0?1:-1];
typedef char Offset_4[FIELD_OFFSET(WORK,distance)==32?1:-1];
typedef char Offset_5[FIELD_OFFSET(WORK,unity)==48?1:-1];
typedef char Offset_6[FIELD_OFFSET(WORLD,objects)==16724?1:-1];
typedef char Offset_7[FIELD_OFFSET(WORLD,word4554)==17748?1:-1];
typedef char Offset_8[FIELD_OFFSET(WORLD,word4558)==17752?1:-1];
typedef char Offset_9[FIELD_OFFSET(WORLD,tree)==17756?1:-1];
typedef char Offset_10[FIELD_OFFSET(WORLD,word4560)==17760?1:-1];
typedef char Offset_11[FIELD_OFFSET(WORLD,leaves)==17764?1:-1];
typedef char Offset_12[FIELD_OFFSET(WORLD,word4568)==17768?1:-1];
typedef char Offset_13[FIELD_OFFSET(WORLD,word456C)==17772?1:-1];
typedef char Offset_14[FIELD_OFFSET(WORLD,mask)==17776?1:-1];
typedef char Offset_15[FIELD_OFFSET(NODE,plane)==0?1:-1];
typedef char Offset_16[FIELD_OFFSET(NODE,left)==16?1:-1];
typedef char Offset_17[FIELD_OFFSET(NODE,right)==20?1:-1];
typedef char Offset_18[FIELD_OFFSET(NODE,leftLeaf)==24?1:-1];
typedef char Offset_19[FIELD_OFFSET(NODE,rightLeaf)==28?1:-1];
typedef char Offset_20[FIELD_OFFSET(OBJ,sphere)==256?1:-1];
typedef char Offset_21[FIELD_OFFSET(SPHERE,position)==0?1:-1];
typedef char Offset_22[FIELD_OFFSET(SPHERE,bias)==16?1:-1];
typedef char Offset_23[FIELD_OFFSET(SPHERE,weight)==20?1:-1];
typedef char Offset_24[FIELD_OFFSET(RESULT,score)==0?1:-1];
typedef char Offset_25[FIELD_OFFSET(RESULT,object)==4?1:-1];
typedef char Size_0[sizeof(U)==16?1:-1];
typedef char Size_1[sizeof(HOME)==16?1:-1];
typedef char Size_2[sizeof(WORK)==64?1:-1];
typedef char Size_3[sizeof(MASK)==32?1:-1];
typedef char Size_4[sizeof(NODE)==32?1:-1];
typedef char Size_5[sizeof(SPHERE)==32?1:-1];
typedef char Size_6[sizeof(OBJ)==288?1:-1];
typedef char Size_7[sizeof(RESULT)==8?1:-1];
typedef char Size_8[sizeof(WORLD)==17808?1:-1];
typedef char Size_9[sizeof(qword)==16?1:-1];
typedef char Size_10[sizeof(uint)==4?1:-1];
typedef char Size_11[sizeof(int)==4?1:-1];
typedef char Size_12[sizeof(float)==4?1:-1];
typedef char Size_13[sizeof(void*)==4?1:-1];
typedef char Alignment_0[__alignof__(U)==16?1:-1];
typedef char Alignment_1[__alignof__(HOME)==16?1:-1];
typedef char Alignment_2[__alignof__(WORK)==16?1:-1];
typedef char Alignment_3[__alignof__(MASK)==16?1:-1];
typedef char Alignment_4[__alignof__(NODE)==16?1:-1];
typedef char Alignment_5[__alignof__(SPHERE)==16?1:-1];
typedef char Alignment_6[__alignof__(OBJ)==16?1:-1];
typedef char Alignment_7[__alignof__(RESULT)==4?1:-1];
typedef char Alignment_8[__alignof__(WORLD)==16?1:-1];
extern "C" void func_001A3F78(WORLD *p, qword pos, int capacity, RESULT *results)
{
    WORK w;
    NODE *n;
    MASK *leaf;
    uint i;
    func_002333B4(results, 0, capacity * sizeof(RESULT));
    w.mask.q[0] = p->mask.q[0];
    w.mask.q[1] = p->mask.q[1];
    if (p->tree) {
        n = p->tree;
        do {
            if (PlaneDistance(&w.distance,&w.unity,n->plane,pos) < 0.0f) {
                if (n->left) n = n->left;
                else { leaf = &p->leaves[n->leftLeaf]; break; }
            } else {
                if (n->right) n = n->right;
                else { leaf = &p->leaves[n->rightLeaf]; break; }
            }
        } while (n);
        for (i = 0; i < 8; i++) w.mask.a[i] |= leaf->a[i];
    }
    for (i = 0; i < 8; i++) {
        uint word = w.mask.a[i];
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
