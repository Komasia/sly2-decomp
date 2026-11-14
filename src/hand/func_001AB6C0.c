/* class: MC, the memory card manager (D_002E65E0; layout as 0x1AB418 / 0x1AC598: port, slot, states, the three
 * 0x5464-byte save slots at +0x24, the Sly 1 MEMCARD thread at +0xFD5C): the card formatted (sceMcFormat); on an error
 * the card state 2 and the memory card prompt D_002E6550 in state 3, else the card state 3. */
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
int sceMcFormat(int port, int slot);
void func_001ACC38(void *pprompt, int state);
extern char D_002E6550[];   /* the memory card prompt */

int func_001AB6C0(MC *pmc)
{
    int nErr = FUN_0018bc90(pmc->memcard, sceMcFormat(pmc->port, pmc->slot), 0x10, 0);

    if (nErr != 0) {
        pmc->stateCard = 2;
        func_001ACC38(D_002E6550, 3);
    } else {
        pmc->stateCard = 3;
    }
    return nErr;
}
