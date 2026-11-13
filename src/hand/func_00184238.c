/* class: a use (cid 0x23 family; SafeHouse jt.cpp method 4: the distance adjusted - less the use's radius +0x110 less
 * (D_002BF660 - 150)). */
struct USE {
    /* 0x000 */ char pad0[0x110];
    /* 0x110 */ float sRadius;   /* field: SafeHouse port (200) */
};
extern float D_002BF660;

void func_00184238(struct USE *puse, float *ps)
{
    *ps -= puse->sRadius - (D_002BF660 - 150.0f);
}
