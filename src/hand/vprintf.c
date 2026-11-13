struct OSTRM { char *pbMem; int cbMemMax; int cbMem; int fd; int cbTotal; int cbBuf; char ab[0x400]; };
void __5OSTRMi(struct OSTRM *p, int fd);
int CchOstrmPrintf(struct OSTRM *p, char *fmt, char *ap) asm("CchOstrmPrintf__FP5OSTRMPcT1");
void func_0020D618(struct OSTRM *p, int f);
int vprintf(char *fmt, char *ap)
{
    struct OSTRM s;
    int r;
    __5OSTRMi(&s, -1);
    r = CchOstrmPrintf(&s, fmt, ap);
    func_0020D618(&s, 2);
    return r;
}
