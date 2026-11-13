/* InitBtn: the defaults of a button component (BTN, inside BUTTON +0x150 / VOLBTN +0x130): no dialog yet, speed 1,
 * a re-arm time of 1 s.
 * name: Sly 1 InitBtn__FP3BTN (called by InitButton / InitVolbtn in the slot where Sly 1 calls InitBtn); the
 * fields: SafeHouse port (trigger.cpp: "+0x8C ... 0x148718: speed 1", "+0x98 ... 1 s by default: 0x148718"). */
struct BTN {
    /* 0x00 */ char pad0[0x8C];
    /* 0x8C */ float svSpeed;     /* field: SafeHouse port (speed, 1) */
    /* 0x90 */ int oid90;         /* -1 (OID_Nil), as Sly 1 InitBtn sets its oidDialog; its use in Sly 2 is not checked */
    /* 0x94 */ int pad94;
    /* 0x98 */ float dtRearm;     /* field: SafeHouse port (pad.cpp dtRearm, 1 s) */
};

void InitBtn__FP3BTN(struct BTN *pbtn)
{
    pbtn->oid90 = -1;
    pbtn->svSpeed = 1.0f;
    pbtn->dtRearm = 1.0f;
}
