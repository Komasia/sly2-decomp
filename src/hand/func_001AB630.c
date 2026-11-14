/* class: MC, the memory card manager (D_002E65E0; layout as 0x1AB418 / 0x1AC598: port, slot, states, the three
 * 0x5464-byte save slots at +0x24, the Sly 1 MEMCARD thread at +0xFD5C): in state 5 with a read slot (D_003E0EA8), the
 * card's slots validated (0x1AC570; SafeHouse frontend.cpp: "the card's slots read at the world's start"), the card
 * state 6, then 0x1AB418 (6: the newest slot chosen). */
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
extern int D_003E0EA8;
void SetMemcardThreadHighPrio__FP7MEMCARD(void *pmemcard);
int func_001AC570(MC *pmc, MCSLOT *pslot);
void func_001AB418(MC *pmc, int stateCard);

void func_001AB630(MC *pmc)
{
    if (pmc->state == 5 && D_003E0EA8 != 0) {
        MCSLOT *pslot = pmc->aslot;
        int i;

        SetMemcardThreadHighPrio__FP7MEMCARD(pmc->memcard);
        for (i = 2; i >= 0; i--) {
            func_001AC570(pmc, pslot);
            pslot++;
        }
        pmc->stateCard = 6;
        func_001AB418(pmc, 6);
    }
}
