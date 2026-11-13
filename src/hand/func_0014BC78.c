extern char D_002A2E50[];
extern char D_002A2E58[];
extern int s_retCdRead;
extern int s_retCdError;
int sceCdRead(unsigned int lsn, unsigned int c, void *buf, void *mode);
int func_241E88(int n);
int sceCdSync(int n);
int sceCdGetError(void);
void ReadCdDirect__FUiUiPv(unsigned int lsn, unsigned int c, void *buf, int fMode)
{
    void *mode;
    if (fMode == 1) mode = D_002A2E50;
    else mode = D_002A2E58;
    do {
        s_retCdRead = sceCdRead(lsn, c, buf, mode);
        if (s_retCdRead == 1) break;
        sceCdSync(0);
        s_retCdError = sceCdGetError();
    } while (1);
}
