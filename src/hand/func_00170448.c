int func_00170448(int n)
{
    if (n >= 9) {
        if (n >= 0x21) {
            if (n < 0x41) return 6;
            return 7;
        }
        if (n < 0x11) return 4;
        return 5;
    }
    if (n >= 3) {
        if (n < 5) return 2;
        return 3;
    }
    if (n == 0) return -1;
    return n >= 2;
}
