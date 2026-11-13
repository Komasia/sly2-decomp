struct BMP { char pad[8]; unsigned short w; unsigned short h; unsigned char psm; unsigned char bw; char pad2[0x18-0xE]; int cqw; };
void BuildImageGifs(int dbp, int dbw, int psm, int w, int h, int cqw, void *pgifs) asm("BuildImageGifs__FiiiiiiP4GIFS");
void func_001ECBF0(struct BMP *pbmp, int dbp, void *pgifs)
{
    BuildImageGifs(dbp, pbmp->bw, pbmp->psm, pbmp->w, pbmp->h, pbmp->cqw, pgifs);
}
