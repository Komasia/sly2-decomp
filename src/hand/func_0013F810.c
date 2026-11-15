/* LoadOptionsFromBrx: the object's options: S16 option ids (EOPID, until a negative one), each loaded by
 * LoadOptionFromBrx with its table entry and flags (grf & 0x2580). SafeHouse port. */
struct EOPID { int otyp; int grf; char pad[0x20]; };   /* 0x28 bytes (SafeHouse cmworld.cpp: VA_AEOPID + eopid * 0x28, grf +4) */
extern struct EOPID D_002AC880[];   /* the option table */
int S16Read(void *) asm("S16Read__18CBinaryInputStream");
void LoadOptionFromBrx__FPvP5EOPIDiP18CBinaryInputStream(void *, struct EOPID *, int, void *);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(void *pv, void *pbis) {
    int eopid;
    while ((eopid = S16Read(pbis)) >= 0) {
        struct EOPID *peopid = &D_002AC880[eopid];
        LoadOptionFromBrx__FPvP5EOPIDiP18CBinaryInputStream(pv, peopid, peopid->grf & 0x2580, pbis);
    }
}
