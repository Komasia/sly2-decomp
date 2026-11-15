/* AttachStandBooty: a stand without booty gets one from the world's booty proxy (SW +0x4638) with the record the save
 * says (IdStandSaved, -1: none), on the stand (state 1). SafeHouse port (booty.cpp, orig 0x13CF38). */
struct BOOTY { char pad[0x15c]; void *pstand; };   /* field: SafeHouse port */
struct SW { char pad[0x4638]; void *pproxyBooty; };   /* the booty proxy */
extern struct SW g_sw;
struct STAND { char pad[0x194]; struct BOOTY *pbooty; };   /* field: SafeHouse port */
int IdStandSaved__FP2LO(struct STAND *);
struct BOOTY *PloAcquireProxyObject__FP2SWi(void *, int);
void SelectBootyRecord__FP2LOi(struct BOOTY *, int);
void SetBootyState__FP2LOi(struct BOOTY *, int);
// name: SafeHouse port (AttachStandBooty)
void AttachStandBooty__FP2LO(struct STAND *pstand) {
    struct SW *psw;
    int id;
    struct BOOTY *pbooty;
    if (pstand->pbooty) return;
    psw = &g_sw;
    if (!psw->pproxyBooty) return;
    id = IdStandSaved__FP2LO(pstand);
    if (id == -1) return;
    pbooty = PloAcquireProxyObject__FP2SWi(psw->pproxyBooty, 0);
    pstand->pbooty = pbooty;
    if (pbooty) {
        SelectBootyRecord__FP2LOi(pbooty, id);
        pstand->pbooty->pstand = pstand;
        SetBootyState__FP2LOi(pstand->pbooty, 1);
    }
}
