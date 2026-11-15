/* FFilterMatches: whether the current world (0x210A88; -1: none, always) is one of the c listed. */
int func_00210A88(void);
// name: SafeHouse port (FFilterMatches)
int FFilterMatches__FiPs(int c, short *aiwrec) {
    int iwrec = func_00210A88();
    int i;
    short *ps;
    if (iwrec == -1)
        return 1;
    for (i = 0; ; i++) {
        if (i >= c)
            return 0;
        if (aiwrec[i] == iwrec)
            break;
    }
    return 1;
}
