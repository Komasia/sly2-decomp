/* A description getter of the load's options (grf 0x2000; SafeHouse jt.cpp FDescGetter): the object's part at
 * +0x130. */
struct LOPART {
    /* 0x000 */ char pad0[0x130];
    /* 0x130 */ char part[4];
};

void *func_00259A48(struct LOPART *plo)
{
    return plo->part;
}
