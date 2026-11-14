/* class: the screen player (SafeHouse splayer.h CScreenPlayer; the screen object's draw 0x213300 calls it first): the
 * root's entry 0 queued for drawing (0x2185F8) while it plays (+0x28; see StopRoot 0x218638). */
typedef struct SENTRYRT {       /* a group entry (SafeHouse splayer.h SENTRYRT; 0x18 bytes) */
    /* 0x00 */ char pad0[8];
    /* 0x08 */ short ipart;         /* the part it plays (-1 none) */
    /* 0x0a */ short ikey;
    /* 0x0c */ char padc[0xc];
} SENTRYRT;
typedef struct SPART { char ab[0x18]; } SPART;
typedef struct SPLAYER {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ SPART *apart;
    /* 0x08 */ SENTRYRT *aentry;
    /* 0x0c */ char padc[0x1c];
    /* 0x28 */ int fPlaying;
} SPLAYER;

void func_002185F8(SPLAYER *psplayer, int ientry, int b);

void func_002185D0(SPLAYER *psplayer)
{
    if (psplayer->fPlaying != 0) {
        func_002185F8(psplayer, 0, 0);
    }
}
