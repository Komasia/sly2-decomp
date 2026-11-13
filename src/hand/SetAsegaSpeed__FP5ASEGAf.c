/* ASEGA: an animation segment's instance on an object (Sly 1 asega.h), only the speed fields here.
 * The playback rate svt is the caller's rate times the master rate and the "suck" scale. */
struct ASEGA {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ float svt;           /* effective rate */
    /* 0x44 */ float svtRate;       /* the rate SetAsegaSpeed was given */
    /* 0x48 */ float svtMaster;
    /* 0x4c */ float svtSuck;
};

void SetAsegaSpeed__FP5ASEGAf(struct ASEGA *pasega, float svt)
{
    pasega->svtRate = svt;
    pasega->svt = svt * pasega->svtMaster * pasega->svtSuck;
}
