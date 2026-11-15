/* The sub-object's message handler: an event of its swing animation: 0x16E the hand record released (the swing's
 * controller on +0x10B8 demoted), 0x242 the swing may chain. Layout: SafeHouse port (gang.h BENTLEYSUB). */
struct BENTLEY { char pad[0x10b8]; void *pxf10B8; };   /* field: SafeHouse port */
struct BENTLEYSUB { struct BENTLEY *pbentley; int pad[2]; int nC; int n10; char pad2[0xe0 - 0x14]; int pasega; };   /* field: SafeHouse port */
struct MSGEV { int id; int f4; int symid; };   /* message 9: an ASEGA event {source, -, event} */
void DemoteAsegaOnXf__FiiP2XF(int, struct BENTLEY *, void *);
void func_00136ED0(struct BENTLEYSUB *psub, int msg, struct MSGEV *pm) {
    if (msg == 9 && pm->id == psub->pasega) {
        switch (pm->symid) {
        case 0x16e: DemoteAsegaOnXf__FiiP2XF(pm->id, psub->pbentley, psub->pbentley->pxf10B8); psub->n10 = 1; break;
        case 0x242: psub->nC = 1; break;
        }
    }
}
