int func_00209A28(unsigned long a, unsigned long b) {
    unsigned long x = a & b;
    int c;
    if (x != a) return 0;
    for (c = 0; x != 0; c++) x &= x - 1;
    return c;
}
