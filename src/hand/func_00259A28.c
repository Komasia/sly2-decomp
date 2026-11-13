/* A description getter of the load's options (grf 0x2000; SafeHouse jt.cpp FDescGetter): the object's part at
 * +0x150. */
struct LOPART {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ char part[4];
};

void *func_00259A28(struct LOPART *plo)
{
    return plo->part;
}
