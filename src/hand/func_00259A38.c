/* A description getter of the load's options (grf 0x2000; SafeHouse jt.cpp FDescGetter): the object's part at
 * +0xE0. */
struct LOPART {
    /* 0x000 */ char pad0[0xe0];
    /* 0x0e0 */ char part[4];
};

void *func_00259A38(struct LOPART *plo)
{
    return plo->part;
}
