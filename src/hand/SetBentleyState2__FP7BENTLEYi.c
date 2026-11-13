/* SetBentleyState2: change Bentley's second state machine (the bombs: +0x16BC) and remember when (+0x16C0); state
 * 0 also ends his sub-object's mode (+0x1710). Layout: SafeHouse port (gang.h BENTLEY). */
struct BENTLEYSUB;
struct BENTLEY {
    /* 0x0000 */ char pad0[0x16bc];
    /* 0x16bc */ int n16BC;     /* field: SafeHouse port - the second state machine */
    /* 0x16c0 */ float t16C0;   /* field: SafeHouse port - when it changed */
    /* 0x16c4 */ char pad16C4[0x1710 - 0x16c4];
    /* 0x1710 */ char sub[4];   /* field: SafeHouse port - the BENTLEYSUB */
};
extern float g_clock;            /* CLOCK +0x0: t */
void SetBentleySubMode(struct BENTLEYSUB *psub, int mode) asm("SetBentleySubMode__FP7BENTLEYi");

// name: SafeHouse port (SetBentleyState2)
void SetBentleyState2__FP7BENTLEYi(struct BENTLEY *pbentley, int n)
{
    if (n != pbentley->n16BC) {
        pbentley->n16BC = n;
        pbentley->t16C0 = g_clock;
        if (n == 0)
            SetBentleySubMode((struct BENTLEYSUB *)pbentley->sub, -1);
    }
}
