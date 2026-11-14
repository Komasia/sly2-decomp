/* class: the screen player (SafeHouse splayer.h CScreenPlayer, module 0x217BA0..0x21A998; 0x215960 calls it for a slot
 * holding a nested group): entry ientry's slots queued for drawing (0x21A998) through the part it plays, if any. */
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

void func_0021A998(SPART *ppart, int ientry, int b);

void func_002185F8(SPLAYER *psplayer, int ientry, int b)
{
    int ipart = psplayer->aentry[ientry].ipart;

    if (ipart >= 0) {
        func_0021A998(&psplayer->apart[ipart], ientry, b);
    }
}
