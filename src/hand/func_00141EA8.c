/* GrfAbilityButton: the buttons the ability id is on (D_002C3258 per slot). SafeHouse port (gadget.h). */
struct ABSLOT { int id; int a, b; };   /* a button's ability slot (SafeHouse gadget.h) */
struct ACTOR { char pad[0x1180]; struct ABSLOT aabslot[3]; };
extern int D_002C3258[];   /* the buttons of the three slots */
// name: SafeHouse port (gadget.h GrfAbilityButton, orig 0x141EA8)
int GrfAbilityButton__FP5ACTORi(struct ACTOR *pactor, int id)
{
    int i;
    int grfbtn = 0;
    for (i = 0; i < 3; i++) {
        if (id == pactor->aabslot[i].id) grfbtn |= D_002C3258[i];
    }
    return grfbtn;
}
