struct G { char pad[0x228]; void *p228; };
extern struct G D_003DD040;
int IvoiceFromTarget__FP8SOUNDMGRi(struct G *);
void SetVoiceVolume__9CSndVoiceif(void *, int, float);
void SetVoicePan__9CSndVoiceii(void *, int, int);
void func_001FF108(int a, int b, int c, float g)
{
    int r = IvoiceFromTarget__FP8SOUNDMGRi(&D_003DD040);
    void *p = D_003DD040.p228;
    SetVoiceVolume__9CSndVoiceif(p, r, g);
    SetVoicePan__9CSndVoiceii(p, r, c);
}
