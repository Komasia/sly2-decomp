typedef struct { void *p; int fl; int n; } ENT;
typedef struct OBJ {
    char pad[0x180];
    int x180;
    int pad184;
    void *x188;
    int c;
    ENT ae[8];
} OBJ;
extern struct G g_sw;
extern char D_003DA150[];
extern char D_002DE2E0[];
extern int g_grfjoyt;
extern char g_joy[];
extern char D_002E0D00[];
void UpdateSo__FP2SOf(OBJ *);
int func_0014FD50(void *);
int func_00187E88(void *);
int GrfbtnTakePressedJoy(void *, int) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
void *func_001F07E8(void *);
OBJ *PloFindSwNearest__FP2LO3OIDii(struct G *, int, int, OBJ *);
void func_001DC260(void *, int);
void StartScptImpl__FP2LOi(OBJ *, int);
void func_001D77D0(OBJ *, int);
// name: SafeHouse port (UpdateSafeHouse)
void UpdateSafeHouse__FP2LO(OBJ *p)
{
    char *pad;
    int n;
    int i;
    ENT *pe;
    UpdateSo__FP2SOf(p);
    if (p->x180 == 0)
        return;
    if (p->x180 != 1)
        return;
    if (p->x188 == 0)
        return;
    if (func_0014FD50(D_002DE2E0))
        return;
    if (g_grfjoyt & 2)
        pad = g_joy;
    else
        pad = D_002E0D00;
    n = func_00187E88(pad);
    if (n == 0) {
        for (i = 0; ; i++) {
            OBJ *q;
            pe = &p->ae[i];
            if (i >= p->c)
                return;
            if (pe->p != func_001F07E8(p->x188))
                continue;
            if (!GrfbtnTakePressedJoy(pad, pe->fl))
                continue;
            if (pe->n == -1)
                continue;
            if (pe->n == 0x378) {
                func_001DC260(D_003DA150, 0);
                break;
            }
            q = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, pe->n, p);
            if (q) {
                StartScptImpl__FP2LOi(q, 0);
                return;
            }
        }
    } else {
        func_001D77D0(p, n);
    }
}
