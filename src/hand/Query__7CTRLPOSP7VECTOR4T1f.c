/* CTRLPOS::Query: a position controller's goal (+0x20) and no velocity. */
typedef int qword __attribute__((mode(TI)));
struct VECTOR3 { float x, y, z; };
struct CTRLPOS {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ qword posGoal;
};

// name: SafeHouse port (CTRLPOS::Query)
void Query__7CTRLPOSP7VECTOR4T1f(struct CTRLPOS *pctrl, qword *ppos, struct VECTOR3 *pvel)
{
    if (ppos)
        *ppos = pctrl->posGoal;
    if (pvel) {
        pvel->z = 0.0f;
        pvel->y = 0.0f;
        pvel->x = 0.0f;
    }
}
