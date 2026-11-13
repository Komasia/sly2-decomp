/* class: SOUNDMGR (SafeHouse spliceglue.cpp, method 0x1021D0 -> 0x1FCFD0: the dialog line's length +0x50, 0 when it
 * has no stream). */
struct SOUNDMGR;
struct STREAM {
    /* 0x00 */ char pad0[0x50];
    /* 0x50 */ float sLength;
};
struct STREAM *PstreamFindDialog__FP8SOUNDMGRi(struct SOUNDMGR *psm, int id);

float func_001FCFD0(struct SOUNDMGR *psm, int id)
{
    struct STREAM *pstream = PstreamFindDialog__FP8SOUNDMGRi(psm, id);
    float s = 0.0f;
    if (pstream != 0) {
        s = pstream->sLength;
    }
    return s;
}
