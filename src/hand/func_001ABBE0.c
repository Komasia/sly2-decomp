/* class: MC, the memory card manager (D_002E65E0; layout as 0x1AB418 / 0x1AC598: port, slot, states, the three
 * 0x5464-byte save slots at +0x24, the Sly 1 MEMCARD thread at +0xFD5C): the card's info (0x1AC598), then the current slot's
 * 0x1AC420; on an error the memory card prompt D_002E6550 shows message 0x23 (state 3) and D_002E65A0's slot 49. */
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
int func_001AC598(MC *pmc);
int FUN_0018d2e8(MC *pmc, int islot);
void func_001ACC38(void *pprompt, int state);
void func_001ACB58(void *pprompt, int msg);
void func_001ADE70(void *pwidget);
extern char D_002E6550[];   /* the memory card prompt */
extern char D_002E65A0[];

int func_001ABBE0(MC *pmc)
{
    int nErr = func_001AC598(pmc);

    if (nErr != 0 || (nErr = FUN_0018d2e8(pmc, pmc->islot)) != 0) {
        func_001ACC38(D_002E6550, 3);
        func_001ACB58(D_002E6550, 0x23);
        func_001ADE70(D_002E65A0);
    }
    return nErr;
}
