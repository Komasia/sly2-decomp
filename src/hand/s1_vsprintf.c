struct OSTRM { char *pbMem; int cbMemMax; int cbMem; int fd; int cbTotal; int cbBuf; char ab[0x400]; };
void func_0020D5F0(struct OSTRM *p, char *pb, int cb);
int CchOstrmPrintf(struct OSTRM *p, char *fmt, char *ap) asm("CchOstrmPrintf__FP5OSTRMPcT1");
void func_0020D618(struct OSTRM *p, int f);
int s1_vsprintf(char *pchzDest, char *fmt, char *ap)
{
    struct OSTRM s;
    int len;
    func_0020D5F0(&s, pchzDest, 0);
    len = CchOstrmPrintf(&s, fmt, ap);
    pchzDest[len] = 0;
    func_0020D618(&s, 2);
    return len;
}
