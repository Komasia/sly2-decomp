/* func_0015EF30: build the two built-in fonts (D_002DE770) from their data (D_002BE320), their bitmaps placed in a
 * VRAM region (ZPR) from 0x1000 to 0x1800. */
struct ZPR { char ab[0x630]; };
struct CFontBrx { char ab[0x140]; };
extern struct CFontBrx D_002DE770[];
extern int D_002BE320[];
void InitZpr(struct ZPR *pzpr, int gsbFirst, int gsbLim) asm("InitZpr__FP3ZPR3ZPKP2LO");
void func_0015F710(struct CFontBrx *pfont, int pfontdata, struct ZPR *pzpr);
void func_0015EF30(void)
{
    struct ZPR zpr;
    int i;
    InitZpr(&zpr, 0x1000, 0x1800);
    for (i = 0; i < 2; i++) {
        int pfontdata = D_002BE320[i];
        func_0015F710(&D_002DE770[i], pfontdata, &zpr);
    }
}
