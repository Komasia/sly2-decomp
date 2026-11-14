/* class: CSidebag (EnsureBasicSidebag / CloneLo call it on a new sidebag): its Splice GC node (packed indices, R10's
 * 0x255DE8 / 0x255C00) taken off its list and put on the list D_002DD2CC, then bit 15 of the node word set. */
typedef struct GCNODE {
    /* 0x0 */ int n0;
    /* 0x4 */ unsigned int grf;   /* the packed prev / next indices; bit 15 a mark */
} GCNODE;

extern GCNODE *D_002DD2CC;
void func_00255DE8(GCNODE *pnode);
void func_00255C00(GCNODE *pnode, GCNODE **pplist);

unsigned int func_00258178(GCNODE *pnode)
{
    func_00255DE8(pnode);
    func_00255C00(pnode, &D_002DD2CC);
    return pnode->grf |= 0x8000;
}
