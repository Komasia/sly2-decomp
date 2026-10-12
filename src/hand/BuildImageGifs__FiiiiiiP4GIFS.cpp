#include "gifs.h"
void BuildImageGifs(int dbp, int dbw, int dpsm, int rrw, int rrh, int cqw, GIFS *pgifs)
{
    pgifs->AddPrimPack(0, 1, 0xE);
    pgifs->PackAD(0x50, ((long)dbp << 32) | ((long)dbw << 48) | ((long)dpsm << 56));
    pgifs->PackAD(0x51, 0);
    pgifs->PackAD(0x52, rrw | ((long)rrh << 32));
    pgifs->PackAD(0x53, 0);
    pgifs->AddImage(cqw);
}
