/* NRandom: a random number below 905010707 (0x35F15E13) from the C library's rand. */
int rand(void);

// name: SafeHouse port (NRandom, xfmath.cpp)
int NRandom__Fv(void)
{
    return rand() % 905010707;
}
