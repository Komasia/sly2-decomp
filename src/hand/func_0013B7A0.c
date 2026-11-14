/* A qsort comparator (used by 0x13B7B8, which sorts an int array and drops the duplicates): the difference of the two
 * element pointers counted in 0x150-byte records, the later element first (as compiled: the pointers themselves,
 * not the ints they point at, are compared). */
typedef struct REC150 { char ab[0x150]; } REC150;

int func_0013B7A0(const REC150 *prec0, const REC150 *prec1)
{
    return prec1 - prec0;
}
