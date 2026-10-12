struct GIFS;
struct CLUT { int grfzon; int n4; unsigned short crgba; unsigned short n; int nC; int cqwColors; };
void BuildImageGifs(int dbp, int dbw, int dpsm, int rrw, int rrh, int cqw, GIFS *pgifs);
void BuildClutGifs(CLUT *pclut, int dbp, GIFS *pgifs)
{
    int dx = (pclut->crgba <= 16) ? 8 : 16;
    BuildImageGifs(dbp, 1, 0, dx, ((pclut->crgba - 1 + dx) & -dx) / dx, pclut->cqwColors, pgifs);
}
