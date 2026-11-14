/* class: an MPEG player's callback (registered by 0x1B3EC0 with sceMpegAddStrCallback / sceMpegAddCallback; the
 * player's data is the third argument): the callback data's bytes (+0x8, +0xC bytes) queued into the player's
 * +0x180 stream (0x1B31E0: CbFill into its byte queues). */
typedef struct MPEGCB {
    /* 0x0 */ int type;
    /* 0x4 */ void *pmpeg;
    /* 0x8 */ unsigned char *pb;
    /* 0xc */ int cb;
} MPEGCB;
typedef struct MOVIE {
    /* 0x000 */ char pad0[0x180];
    /* 0x180 */ char stream[0x80];
} MOVIE;

int func_001B31E0(void *pstream, int cb, unsigned char *pb);

void func_001B33C8(void *pmpeg, MPEGCB *pcb, MOVIE *pmovie)
{
    func_001B31E0(pmovie->stream, pcb->cb, pcb->pb);
}
