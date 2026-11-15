/* class: the title's language menu (an entry's choice, see func_001DD920): set the entry's language, then a world transition
 * through RequestTransition (oid 0x189). */
struct MENUENT { char p0[8]; void *lang; };
extern char g_sw[];
void func_001A2BD0(void *lang);        /* set the language */
void RequestTransition__FP2SWPUc3OIDT2iT2(void *g, int a, int b, int c, int d, int e);
void func_001DD8E0(struct MENUENT *pent) {
    func_001A2BD0(pent->lang);
    RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, 0, 0x189, -1, 1, -1);
}
