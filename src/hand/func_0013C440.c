/* class: CID_67, the booty (EOPID 1153 -> 0x13C440, SafeHouse booty.cpp: no current record). */
struct BOOTYREC;
struct BOOTY {
    /* 0x000 */ char pad0[0x158];
    /* 0x158 */ struct BOOTYREC *precCur;   /* the current record (r9: +0x158 is the record pointer) */
};

void func_0013C440(struct BOOTY *pbooty)
{
    pbooty->precCur = 0;
}
