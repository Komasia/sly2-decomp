/* libmpeg (sceMpeg; called by the movie code 0x1B3BD0): the first word of the decoder's internal data (+0x40). */
typedef struct SCEMPEG {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int *sys;
} SCEMPEG;

int func_0024B610(SCEMPEG *mp)
{
    return *mp->sys;
}
