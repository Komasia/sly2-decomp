/* CompareSaves: order two save-file entries by their modification date, oldest first (a qsort-style comparison).
 * The entry is the one FUN_0018b780 fills from a memory card directory entry (sceMcTblGetDir). */
typedef struct MCDATE {
    unsigned char bMonth;
    unsigned char bDay;
    unsigned short nYear;
    unsigned char bHour;
    unsigned char bMinute;
    unsigned char bSecond;
    unsigned char bPad;
} MCDATE;

struct SAVE {
    /* 0x00 */ char achName[0x44];
    /* 0x44 */ int cb;
    /* 0x48 */ unsigned short grfattr;
    /* 0x4a */ MCDATE dateCreate;
    /* 0x52 */ MCDATE dateModify;
};

int CompareSaves__FP4SAVET0(struct SAVE *psave1, struct SAVE *psave2)
{
    int d = psave1->dateModify.nYear - psave2->dateModify.nYear;
    if (d == 0) {
        d = psave1->dateModify.bMonth - psave2->dateModify.bMonth;
        if (d == 0) {
            d = psave1->dateModify.bDay - psave2->dateModify.bDay;
            if (d == 0) {
                d = psave1->dateModify.bHour - psave2->dateModify.bHour;
                if (d == 0) {
                    d = psave1->dateModify.bMinute - psave2->dateModify.bMinute;
                    if (d == 0)
                        return psave1->dateModify.bSecond - psave2->dateModify.bSecond;
                }
            }
        }
    }
    return d;
}
