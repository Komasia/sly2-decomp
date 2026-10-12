struct GIFS;
struct CLUT { int a; int b; unsigned short cColor; short pad; int c; int cqwPal; };
void BuildImageGifs(int dbp, int dbw, int dpsm, int rrw, int rrh, int cqw, GIFS *pgifs);
void BuildClutGifs(CLUT *pclut, int gsb, GIFS *pgifs)
{
    int rrw = (pclut->cColor > 16) ? 16 : 8;
    int rrh = ((pclut->cColor + (rrw - 1)) & -rrw) / rrw;
    BuildImageGifs(gsb, 1, 0, rrw, rrh, pclut->cqwPal, pgifs);
}
