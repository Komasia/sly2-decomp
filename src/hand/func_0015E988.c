/* func_0015E988: whether class cidBase is cid or derives from it: walks cidBase's chain in the class descriptor
 * table (D_002BAAE8, 0x14 bytes per class). */
struct CLSD { struct CLSD *pclsdBase; int cid; int pad[3]; };
extern struct CLSD D_002BAAE8[];
int func_0015E988(int cidBase, int cid)
{
    struct CLSD *pclsd;
    for (pclsd = &D_002BAAE8[cidBase]; pclsd; pclsd = pclsd->pclsdBase)
        if (pclsd->cid == cid)
            return 1;
    return 0;
}
