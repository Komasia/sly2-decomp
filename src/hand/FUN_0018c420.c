/* FUN_0018c420 (0x1ABA10): reads the saves on the card: without the save directory (sceMcGetDir finds no entry)
 * the card is MCS_NO_SPACE when it has less than 0x19000 bytes free, and the result is 0xE; else the three slots
 * are read (0x1AC4C8) and the card is at least MCS_SAVES. Layout: include/h5_mc.h. */
struct B { char data[0x5464]; };
struct S { int x0; int x4; int x8; int xC; int pad[5]; struct B a[3]; char pad2[0xFD5C - 0x24 - 3 * 0x5464]; char xFD5C[1]; };
extern char g_szSaveDirPath[] __asm__("D_002A6BB0");  /* "/BASCUS-97316YAOTWTD!" */
#define CB_SAVE_MIN 0x19000
int sceMcGetDir(int a, int b, char *c, int d, int e, int f);
int func_001AB098(void *p, int a, int b, int *c);
int func_001AC6A0(struct S *s, int *out);
int func_001AC4C8(struct S *s, struct B *b);
int FUN_0018c420(struct S *s)
{
    void *p = s->xFD5C;
    int n[2];
    int r;
    int i;
    r = func_001AB098(p, sceMcGetDir(s->x0, s->x4, g_szSaveDirPath, 0, -1, 0), 0xD, &n[0]);
    if (n[0] <= 0) {
        func_001AC6A0(s, &n[1]);
        if (n[1] < CB_SAVE_MIN)
            s->xC = 4;
        return 0xE;
    }
    for (i = 0; r == 0 && i < 3; i++)
        func_001AC4C8(s, &s->a[i]);
    if (r == 0 && s->xC < 5)
        s->xC = 5;
    return r;
}
