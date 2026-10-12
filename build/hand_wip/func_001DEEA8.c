/* 22 diffs: gcc turns (q->aep[0].p == p) index into movn select; target uses sltiu/sll 6/addu. Also reg alloc. */
typedef struct { int a, b; } PAIR;
typedef struct OBJ OBJ;
typedef struct EP { void *p; char pad[0x3C]; } EP;
typedef struct LNK {
    char pad[8];
    EP aep[2];
    char pad88[0xAC - 0x88];
    struct LNK *pNext;
} LNK;
typedef struct { char pad[0x148]; LNK *pHead; char pad14c[4]; } ENT;
struct OBJ {
    char pad[0x198];
    int c;
    ENT *ae;
};
extern struct G D_003DD490;
extern PAIR D_002A7AC0;
void func_001F5988(void);
void func_001A7E10(struct G *, LNK *);
void func_00149AB8(struct G *, OBJ *, PAIR, int);
void func_001DEEA8(OBJ *p, void *x)
{
    LNK *list = 0;
    int i;
    func_001F5988();
    for (i = 0; i < p->c; i++) {
        LNK **pp = &p->ae[i].pHead;
        LNK *q;
        while ((q = *pp) != 0) {
            if (x == ((EP *)((char *)q->aep + ((q->aep[0].p == p) << 6)))->p) {
                *pp = q->pNext;
                q->pNext = list;
                list = q;
            } else {
                pp = &q->pNext;
            }
        }
    }
    func_001A7E10(&D_003DD490, list);
    func_00149AB8(&D_003DD490, p, D_002A7AC0, 0);
}
