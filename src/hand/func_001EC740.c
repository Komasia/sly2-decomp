struct E { int a; int b; unsigned int p; int c; int d; };
extern struct E D_003DA798[];
void func_001EC740(int iFirst, int iLast, int cb, unsigned int pOld, unsigned int pNew)
{
    int i;
    unsigned int pEnd = pOld + cb;
    for (i = iFirst; i < iLast; i++) {
        struct E *pe = &D_003DA798[i];
        if (pe->p >= pOld && pe->p < pEnd) pe->p = pNew + (pe->p - pOld);
    }
}
