/* class: LO (a qsort comparator of LO pointers, used by UpdateVolbtn 0x149440 to sort the objects found in the
 * button's volume): by address (LO is 0x50 bytes, cls.h class 2). */
typedef struct LO { char ab[0x50]; } LO;

int func_00149420(LO *const *pplo0, LO *const *pplo1)
{
    return *pplo0 - *pplo1;
}
