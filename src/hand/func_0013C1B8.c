/* OnBootyMessage: message 4 puts a thrown booty (5) out of the world (0); message 8 about its flight (+0x18C) ends it:
 * from the stand it is carried (2 -> 4), onto a stand it stands (3 -> 1). Layout: SafeHouse port (booty.h). */
struct BOOTY { char pad[0x184]; int state; float tState; int pflight; };   /* field: SafeHouse port */
void func_00133590(struct BOOTY *, int, int);
void SetBootyState__FP2LOi(struct BOOTY *, int);
// name: SafeHouse port (OnBootyMessage)
void OnBootyMessage__FP2LOii(struct BOOTY *pbooty, int msg, int a) {
    func_00133590(pbooty, msg, a);
    switch (msg) {
    case 4:
        if (pbooty->state == 5) SetBootyState__FP2LOi(pbooty, 0);
        break;
    case 8:
        if (a == pbooty->pflight) {
            switch (pbooty->state) {
            case 2: SetBootyState__FP2LOi(pbooty, 4); break;
            case 3: SetBootyState__FP2LOi(pbooty, 1); break;
            }
        }
        break;
    }
}
