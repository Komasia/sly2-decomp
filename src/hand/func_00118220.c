typedef struct CBinaryInputStream CBinaryInputStream;
typedef struct MSG { int cb; int nKind; } MSG;
typedef struct ITEM { char ab[0x20]; } ITEM;
typedef struct OWNER { char pad[0xC]; ITEM *aitem; } OWNER;
typedef struct NODE { struct NODE *pnodeLeft; struct NODE *pnodeRight; void *pv; } NODE;
typedef struct TREE { int cnode; int n4; int n8; NODE *anode; } TREE;

int U32Read(CBinaryInputStream *pbis) asm("U32Read__18CBinaryInputStream");
int U16Read(CBinaryInputStream *pbis) asm("U16Read__18CBinaryInputStream");
void *PvAllocSwClearImpl__Fi(MSG *pmsg);
extern char D_002BBAF0[];

void func_00118220(CBinaryInputStream *pbis, OWNER *powner, TREE *ptree)
{
    int i;
    MSG msg;

    ptree->cnode = U32Read(pbis);
    ptree->n4 = U32Read(pbis);
    ptree->n8 = U32Read(pbis);
    msg.cb = ptree->cnode * sizeof(NODE);
    msg.nKind = 0x10;
    ptree->anode = (NODE *)PvAllocSwClearImpl__Fi(&msg);

    for (i = 0; i < ptree->cnode; i++) {
        NODE *pnode = &ptree->anode[i];
        unsigned int iitem = U16Read(pbis);
        if (iitem == 0xFFFF) {
            pnode->pv = D_002BBAF0;
        } else {
            unsigned int inode;
            pnode->pv = &powner->aitem[iitem];
            inode = U32Read(pbis);
            if (inode != 0xFFFFFFFF) {
                pnode->pnodeLeft = &ptree->anode[inode];
            }
            inode = U32Read(pbis);
            if (inode != 0xFFFFFFFF) {
                pnode->pnodeRight = &ptree->anode[inode];
            }
        }
    }
}
