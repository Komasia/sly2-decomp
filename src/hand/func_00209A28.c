/* func_00209A28 (0x209A28): how well a kind entry's mask fits the state mask: 0 unless every state of grfKind is set
 * in grfState, else the number of its states. */
int func_00209A28(unsigned long grfKind, unsigned long grfState) {
    unsigned long grf = grfKind & grfState;
    int cst;
    if (grf != grfKind) return 0;
    for (cst = 0; grf != 0; cst++) grf &= grf - 1;
    return cst;
}
