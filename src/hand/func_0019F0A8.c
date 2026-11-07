struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { int a, b, c; struct VTE *vt; };
struct G;
extern struct G g_sw;
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *, int, int, int, int, struct O **);
// name: SafeHouse port (NotifyPlayersPowerups)
void NotifyPlayersPowerups__Fv(void) {
    struct O *ap[8];
    int c, i;
    c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 5, 0x34, 0, 8, ap);
    for (i = 0; i < c; i++) { struct O *o = ap[i]; struct VTE *e = &o->vt[104]; e->pfn((char *)o + e->d); }
}
