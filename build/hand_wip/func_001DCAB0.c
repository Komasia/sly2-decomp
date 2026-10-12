typedef struct { int x0; int x4; int cost; int xC; int x10; int ids1; int ids2; int x1C; } REC;
typedef struct { char *name; int ids; int pad; } REC2;
typedef struct {
    char pad[0x30];
    int x30;
    int pad34;
    int x38;
    int pad3c;
    int x40;
    char pad44[0x254 - 0x44];
    int x254;
    int x258;
} TBL;
extern TBL D_003DA150;
extern REC D_002BCD00[];
extern REC2 D_002C3288[];
extern struct G D_003DD490;
extern char D_002DEB30[];
extern char D_002A7A38[];
char *func_0013E368(struct G *, int);
int func_00161798(void *);
int func_0021ECD8(char *, const char *, ...);
char *func_0021ED58(char *, const char *);
void func_001DCAB0(char *pch)
{
    TBL *pt = &D_003DA150;
    int ids;
    if (pt->x30 != -1) {
        ids = pt->x38;
    } else {
        switch (pt->x40) {
        case 0: {
            unsigned int i = pt->x254;
            if (i < 0x2B) {
                if (D_002BCD00[i].ids2 != pt->x30) {
                    int idsT = func_00161798(D_002DEB30) < D_002BCD00[i].cost ? 0xD9 : 0xDA;
                    char *pch1 = func_0013E368(&D_003DD490, D_002BCD00[i].ids1);
                    char *pch2 = func_0013E368(&D_003DD490, D_002BCD00[i].ids2);
                    func_0021ECD8(pch, D_002A7A38, pch1, pch2, func_0013E368(&D_003DD490, idsT));
                    return;
                }
            }
            ids = 0xDC;
            break;
        }
        case 1: {
            unsigned int i = pt->x258;
            if (i < 0x40) {
                func_0021ECD8(pch, func_0013E368(&D_003DD490, 0xDB), D_002C3288[i].name);
                return;
            }
            ids = 0xE3;
            break;
        }
        default:
            *pch = 0;
            return;
        }
    }
    func_0021ED58(pch, func_0013E368(&D_003DD490, ids));
}
