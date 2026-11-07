// Remove contacts linking the owner to the selected object.
typedef struct { short kind,index; union { short item; int value; } payload; } PAIR;
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
extern struct G g_sw;
extern PAIR D_002A7AC0;
void SetAloOverlapNothing__FP3ALOT0(void);
void func_001A7E10(struct G *, LNK *);
void func_00149AB8(struct G *, OBJ *, PAIR, int);
// name: SafeHouse port (RemoveLaserContacts)
void RemoveLaserContacts__FP3ALOT0(OBJ *p, void *x)
{
    LNK *list = 0;
    int i;
    SetAloOverlapNothing__FP3ALOT0();
    for (i = 0; i < p->c; i++) {
        LNK **pp = &p->ae[i].pHead;
        LNK *q;
        while ((q = *pp) != 0) {
            int side = q->aep[0].p == p;
            if (x == ((EP *)((char *)q+((unsigned int)side<<6)+8))->p) {
                *pp = q->pNext;
                q->pNext = list;
                list = q;
            } else {
                pp = &q->pNext;
            }
        }
    }
    func_001A7E10(&g_sw, list);
    func_00149AB8(&g_sw, p, D_002A7AC0, 0);
}
