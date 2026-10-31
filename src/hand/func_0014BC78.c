extern char D_002A2E50[];
extern char D_002A2E58[];
extern int s_retCdRead;
extern int s_retCdError;
int func_00242840(unsigned int lsn, unsigned int c, void *buf, void *mode);
int func_241E88(int n);
int func_00241E88(int n);
int func_00242AE0(void);
void ReadCdDirect__FUiUiPv(unsigned int lsn, unsigned int c, void *buf, int fMode)
{
    void *mode;
    if (fMode == 1) mode = D_002A2E50;
    else mode = D_002A2E58;
    do {
        s_retCdRead = func_00242840(lsn, c, buf, mode);
        if (s_retCdRead == 1) break;
        func_00241E88(0);
        s_retCdError = func_00242AE0();
    } while (1);
}
