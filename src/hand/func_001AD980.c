/* func_001AD980 (0x1AD980): a save slot's description line (format D_002A6EC8): unless the menu widget D_003DA530
 * says not to, the current world's name string and the game's completion percentage. */
struct G { char pad[0x3A18]; char x3A18[1]; };
extern struct G g_sw;
extern char D_003DA530[], D_002A6EC8[], D_003D4A60[];
int func_001D9880(void *p);
void *func_00210B28(void);
int func_001DDD40(void *p);
char *func_0013E368(void *p, int n);
char *NGamePercent__FPvPUc(void *p, void *q);
void sprintf(char *buf, char *fmt, ...);
void func_001AD980(char *szOut)
{
    char *a;
    struct G *g;
    char *fmt;
    if (func_001D9880(D_003DA530))
        return;
    fmt = D_002A6EC8;
    g = &g_sw;
    a = func_0013E368(g, func_001DDD40(func_00210B28()));
    sprintf(szOut, fmt, a, NGamePercent__FPvPUc(g->x3A18, D_003D4A60));
}
