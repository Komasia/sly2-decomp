enum UPK { UPK_0 };
struct VIFS { void AddVifUnpack(UPK upk, int c, void *pv, int iqw); };
void func_00226E88(VIFS *pvifs, UPK upk, int c, int iqw, int *pcb, unsigned int **ppw);
void VIFS::AddVifUnpack(UPK upk, int c, void *pv, int iqw)
{
    int cb;
    unsigned int *pw;
    unsigned int *pwSrc = (unsigned int *)pv;
    func_00226E88(this, upk, c, iqw, &cb, &pw);
    unsigned int *pwDst = pw;
    int cw = (cb + 3) >> 2;
    int cRem = cw & 3;
    int cBlk = cw - cRem;
    int i;
    for (i = 0; i < cRem; i++) *pwDst++ = *pwSrc++;
    for (i = 0; i < cBlk; i += 4) {
        unsigned int a = pwSrc[0], b = pwSrc[1], c2 = pwSrc[2], d = pwSrc[3];
        pwDst[0] = a; pwDst[1] = b; pwDst[2] = c2; pwDst[3] = d;
        pwSrc += 4; pwDst += 4;
    }
}
