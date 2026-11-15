// BuildImageGifs (Sly 1 gs.c): a GIF packet that uploads an image (cqw qwords) to GS memory: BITBLTBUF (the
// destination base / width / format), TRXPOS, TRXREG (the size), TRXDIR (host to local), then the IMAGE data.
#include "gifs.h"
#include "h2_gs.h"
void BuildImageGifs(int dbp, int dbw, int dpsm, int rrw, int rrh, int cqw, GIFS *pgifs)
{
    pgifs->AddPrimPack(0, 1, GIF_REG_AD);
    pgifs->PackAD(GS_REG_BITBLTBUF, ((long)dbp << 32) | ((long)dbw << 48) | ((long)dpsm << 56));
    pgifs->PackAD(GS_REG_TRXPOS, 0);
    pgifs->PackAD(GS_REG_TRXREG, rrw | ((long)rrh << 32));
    pgifs->PackAD(GS_REG_TRXDIR, 0);
    pgifs->AddImage(cqw);
}
