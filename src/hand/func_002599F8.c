/* A description getter of the load's options (grf 0x2000; SafeHouse jt.cpp FDescGetter): the object's part at
 * +0x190. */
struct LOPART {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ char part[4];
};

void *func_002599F8(struct LOPART *plo)
{
    return plo->part;
}
