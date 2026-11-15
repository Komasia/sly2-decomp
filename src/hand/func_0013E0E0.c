/* LoadNodesFromBrx: the world's node tree (SW +0x4558): U16 count, then per node its position and two S16 children
 * (-1: a leaf, numbered in order); then room for the leaves (0x20 bytes each). SafeHouse port. */
struct AREQ { int cb; int cbAlign; };
struct NODE { char pad[0x10]; struct NODE *pnodeA; struct NODE *pnodeB; int ileafA; int ileafB; };   /* a position, then two children (or leaf indices) */
struct SW { char pad[0x4558]; int cnode; struct NODE *anode; int cleaf; void *aleaf; };
int U16Read(void *pbs) asm("U16Read__18CBinaryInputStream");
void ReadVector4__18CBinaryInputStreamP7VECTOR4(void *pbs, struct NODE *pnode);
int S16Read(void *pbs) asm("S16Read__18CBinaryInputStream");
void *PvAllocSwClearImpl__Fi(struct AREQ *preq);
// name: SafeHouse port (LoadNodesFromBrx)
void LoadNodesFromBrx__FP2SWP18CBinaryInputStream(struct SW *psw, void *pbs)
{
    struct AREQ req;
    int i;
    int c = U16Read(pbs);
    req.cbAlign = 0x10;
    req.cb = c * sizeof(struct NODE);
    psw->cnode = c;
    psw->anode = (struct NODE *)PvAllocSwClearImpl__Fi(&req);
    psw->cleaf = 0;
    for (i = 0; i < psw->cnode; i++) {
        struct NODE *pnode = &psw->anode[i];
        int j;
        ReadVector4__18CBinaryInputStreamP7VECTOR4(pbs, pnode);
        j = S16Read(pbs);
        if (j >= 0)
            pnode->pnodeA = &psw->anode[j];
        else
            pnode->ileafA = psw->cleaf++;
        j = S16Read(pbs);
        if (j >= 0)
            pnode->pnodeB = &psw->anode[j];
        else
            pnode->ileafB = psw->cleaf++;
    }
    req.cbAlign = 0x10;
    req.cb = psw->cleaf * sizeof(struct NODE);
    psw->aleaf = PvAllocSwClearImpl__Fi(&req);
}
