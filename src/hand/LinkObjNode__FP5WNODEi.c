/* LinkObjNode: push a node onto a WNODE object's list (+0x138, linked through the node's +0x8) and wake the
 * object. */
struct NODE {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ struct NODE *pnodeNext;
};
struct WNODE {
    /* 0x000 */ char pad0[0x138];
    /* 0x138 */ struct NODE *pnodeFirst;
};
void WakeAlo(struct WNODE *pwnode) asm("WakeAlo__FP3ALO");

// name: SafeHouse port (LinkObjNode)
void LinkObjNode__FP5WNODEi(struct WNODE *pwnode, struct NODE *pnode)
{
    pnode->pnodeNext = pwnode->pnodeFirst;
    pwnode->pnodeFirst = pnode;
    WakeAlo(pwnode);
}
