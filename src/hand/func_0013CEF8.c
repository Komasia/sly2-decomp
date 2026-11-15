/* PostLoadBootyStand: the base post-load (0x183F50), then the stand's id from the world's counter (SW +0x463C).
 * SafeHouse port (booty.cpp). */
struct SW { char pad[0x463c]; int cstand; };   /* the stands' counter */
extern struct SW g_sw;
struct STAND { char pad[0x180]; int id; };   /* the booty stand (cid 0x25) */
void func_00183F50(struct STAND *);
// name: SafeHouse port (PostLoadBootyStand)
void PostLoadBootyStand__FP2SW(struct STAND *pstand) { func_00183F50(pstand); pstand->id = g_sw.cstand++; }
