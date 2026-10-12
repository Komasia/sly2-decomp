typedef int qword __attribute__((mode(TI)));
struct WRE { int wrek; int i; int pad[2]; qword a; qword b; char pad2[0x30]; int k; char pad4[0x6C]; };
struct WR { char pad[0x50]; float f50; int cwre; int c58; int i5C; WRE awre[8]; char pad6[0x6E0 - 0x60 - 0xD0 * 8]; int c6E0; };
extern qword D_002A2DA0;
void AddWrCircleWarp(WR *pwr)
{
    WRE *pwre = &pwr->awre[pwr->cwre++];
    pwr->c6E0++;
    pwre->wrek = 0;
    pwre->a = D_002A2DA0;
    if (pwr->i5C >= 0) {
        pwre->i = pwr->i5C;
        pwr->i5C = -1;
        pwre->k = 2;
    } else {
        pwre->i = pwr->c58++;
        pwr->i5C = pwre->i;
        pwre->k = 0;
    }
}
