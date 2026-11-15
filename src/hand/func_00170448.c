/* func_00170448: the size class of a block of n (VRAM) units: -1 for 0, else 0..7 by powers of two (1, 2, 3..4,
 * 5..8, 9..16, 17..32, 33..64, 65+). */
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
