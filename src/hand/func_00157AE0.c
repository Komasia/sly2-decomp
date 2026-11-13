typedef struct RPL { int k; float z; int a, b; } RPL;
extern int NCmpPrplReverseZ(const void *, const void *) asm("NCmpPrplReverseZ__FPP3RPLT0");
extern int func_00157A98(const void *, const void *);
extern void qsort(void *, int, int, int (*)(const void *, const void *));
// name: Sly 1 CprplPartitionArpl (counting sort of the RPLs by kind, called first by DrawSw; Sly 2 adds the aiFirst / ac outputs)
int CprplPartitionArpl(int c, RPL *arpl, RPL **aprpl, int *aiFirst, int *ac) asm("CprplPartitionArpl__FiP3RPLPP3RPLPiT3");
int CprplPartitionArpl(int c, RPL *arpl, RPL **aprpl, int *aiFirst, int *ac)
{
    int ai[26];
    int i;
    RPL *prpl;
    for (i = 25; i >= 0; i--)
        ac[i] = 0;
    {int j; for (j = 0, prpl = arpl; j < c; j++, prpl++)
        ac[prpl->k]++;}
    aiFirst[0] = 0;
    ai[0] = 0;
    for (i = 1; i < 26; i++) {
        int t;
        aiFirst[i] = t = ac[i - 1];
        ac[i] += t;
        ai[i] = aiFirst[i];
    }
    {int k; for (k = 0; k < c; k++, arpl++)
        aprpl[ai[arpl->k]++] = arpl;}
    qsort(aprpl + aiFirst[5], ac[5] - aiFirst[5], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[6], ac[6] - aiFirst[6], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[10], ac[10] - aiFirst[10], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[1], ac[1] - aiFirst[1], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[2], ac[2] - aiFirst[2], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[25], ac[25] - aiFirst[25], 4, NCmpPrplReverseZ);
    qsort(aprpl + aiFirst[21], ac[21] - aiFirst[21], 4, func_00157A98);
    return ac[25];
}
