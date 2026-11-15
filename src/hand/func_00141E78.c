/* The slot (0..2) holding the ability id on the actor's buttons (+0x1180), -1 when none. */
struct ABSLOT { int id; int a, b; };   /* a button's ability slot (SafeHouse gadget.h) */
struct ACTOR { char pad[0x1180]; struct ABSLOT aabslot[3]; };
int func_00141E78(struct ACTOR *pactor, int id)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (id == pactor->aabslot[i].id) return i;
    }
    return -1;
}
