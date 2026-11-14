/* class: MC, the memory card manager (D_002E65E0; layout as 0x1AB418 / 0x1AC598: port, slot, states, the three
 * 0x5464-byte save slots at +0x24, the Sly 1 MEMCARD thread at +0xFD5C): a file opened on the card (sceMcOpen); its descriptor
 * returned through pfd. */
typedef struct MEMCARD MEMCARD;   /* memcard.h (Sly 1): the worker thread state, +0xFD5C */
typedef struct MCSLOT { char ab[0x5464]; } MCSLOT;   /* a save slot (the save data, its header at +0x5408) */
typedef struct MC {
    /* 0x0000 */ int port;
    /* 0x0004 */ int slot;
    /* 0x0008 */ int state;
    /* 0x000c */ int stateCard;      /* 2 / 3 / 6 (6: the folder read) */
    /* 0x0010 */ char pad10[0x14];
    /* 0x0024 */ MCSLOT aslot[3];
    /* 0xfd50 */ int islot;
    /* 0xfd54 */ MCSLOT *pslotCur;
    /* 0xfd58 */ int nfd58;
    /* 0xfd5c */ char memcard[0x14];  /* MEMCARD */
} MC;
int FUN_0018bc90(void *pmemcard, int nResult, int kind, int *pn);   /* the sceMc call waited for (0x1AB098) */
int sceMcOpen(int port, int slot, const char *szFile, int mode);

int func_001AC7A0(MC *pmc, const char *szFile, int mode, int *pfd)
{
    return FUN_0018bc90(pmc->memcard, sceMcOpen(pmc->port, pmc->slot, szFile, mode), 2, pfd);
}
