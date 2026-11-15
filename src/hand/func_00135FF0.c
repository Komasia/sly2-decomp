/* Whether Bentley is in a ground state (standing, walking, near a target or running). */
struct BENTLEY { char pad[0x13d0]; int state; };
int func_00135FF0(struct BENTLEY *pbentley) {
    switch (pbentley->state) {
    case 0: case 1: case 5: case 7: return 1;
    }
    return 0;
}
