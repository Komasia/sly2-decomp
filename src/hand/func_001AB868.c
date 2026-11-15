/* func_001AB868 (0x1AB868): creates the save on the card (the PMF D_002A6D88): the clusters it needs (the root's
 * entry space: 1, or 2 without any; 5; the icon; 0x42 for the three slots) against the free ones (1: too little room),
 * then the directory with its icon (0x1AB7D0) and the three slots written fresh; the card is then at least
 * MCS_SAVES. On a failure the slots, icon.sys, the icon, the index and the directory are deleted again; an error puts
 * the memory card prompt in state 3. Layout: include/h5_mc.h. */
struct B { char data[0x5464]; };
struct S { int x0; int x4; int x8; int xC; int x10, x14, x18; int x1C; int x20; struct B a[3]; char pad2[0xFD5C - 0x24 - 3 * 0x5464]; char xFD5C[1]; };
extern char g_szRoot[] __asm__("D_002A6C00");         /* "/" */
extern char g_abIcon[] __asm__("D_002A38E8");         /* the built-in icon */
extern char g_szIconSys[] __asm__("D_002A6C08");      /* "/BASCUS-97316YAOTWTD!/icon.sys" */
extern char g_szIconFile[] __asm__("D_002A6C28");     /* "/BASCUS-97316YAOTWTD!/memcard_icon.ico" */
extern char g_szSaveIndex[] __asm__("D_002A6BC8");    /* "/BASCUS-97316YAOTWTD!/BASCUS-97316YAOTWTD!" */
extern char g_szSaveDirPath[] __asm__("D_002A6BB0");  /* "/BASCUS-97316YAOTWTD!" */
extern char D_002E6550[];
int sceMcGetEntSpace(int a, int b, char *c);
int func_001AB098(void *p, int a, int b, int *c);
int func_001AB750(void *p);
int func_001AB7D0(struct S *s);
int func_001AC468(struct S *s, struct B *b);
void func_001ABB10(struct S *s, struct B *b, char *name);
void func_001ACA40(struct S *s, char *name);
void func_001ACC38(void *p, int n);
int func_001AB868(struct S *s)
{
    char name[0x50];
    int cEntFree;
    int cclusterNeed;
    int r;
    int i;
    void *p = s->xFD5C;
    cclusterNeed = 1;
    r = func_001AB098(p, sceMcGetEntSpace(s->x0, s->x4, g_szRoot), 0x12, &cEntFree);
    if (r == 0) {
        if (!cEntFree)
            cclusterNeed = 2;
        cclusterNeed += 5;
        cclusterNeed += (func_001AB750(g_abIcon) + 0x3FF) / 0x400;
        cclusterNeed += 0x42;
        if (s->x1C < cclusterNeed) {
            r = 1;
        } else {
            r = func_001AB7D0(s);
            if (r == 0) {
                for (i = 0; i < 3; i++) {
                    r = func_001AC468(s, &s->a[i]);
                    if (r)
                        goto cleanup;
                }
                if (s->xC < 5)
                    s->xC = 5;
                goto done;
            }
cleanup:
            for (i = 0; i < 3; i++) {
                func_001ABB10(s, &s->a[i], name);
                func_001ACA40(s, name);
            }
            func_001ACA40(s, g_szIconSys);
            func_001ACA40(s, g_szIconFile);
            func_001ACA40(s, g_szSaveIndex);
            func_001ACA40(s, g_szSaveDirPath);
        }
    }
    if (r)
        func_001ACC38(D_002E6550, 3);
done:
    return r;
}
