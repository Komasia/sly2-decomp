struct EYES { char pad[0x64]; int n64; char pad2[0x74-0x68]; float g74; float g78; };
void SetEyesEyess(struct EYES *p, int eyess) asm("SetEyesEyess__FP4EYES5EYESS");
void SetSaiIframe__FP3SAIi(struct EYES *p, int iframe);
void SetEyesClosed__FP4EYESf(struct EYES *p, float g)
{
    p->g78 = g;
    if (g >= 1.0f) {
        SetEyesEyess(p, 2);
    } else {
        p->n64 = -1;
        SetEyesEyess(p, 0);
    }
    SetSaiIframe__FP3SAIi(p, (int)p->g74);
}
