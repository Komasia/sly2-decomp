struct P { char pad[0xC]; void *pvt; char pad2[0x60 - 0x10]; int n60; char pad3[0x70 - 0x64]; float a[6]; char pad4[0x3B8 - 0x88]; int n3B8; };
struct G { char pad[0x58]; int n58; char pad2[0x15C - 0x5C]; float a[1]; };
extern struct G D_003DD040;
extern char D_002D9BE0[];
void func_001FAFD0(struct P *);
void SetDirty__4CSndUiUi(struct P *, int, int);
int ItrackFromStream__FP8SOUNDMGRP9SNDSTREAM(struct G *, int);
void Pause__4CSnd(struct P *);
// name: SafeHouse port (CSndVoice::CSndVoice)
struct P *__9CSndVoiceii(struct P *p, int n, int m)
{
    int i;
    struct G *pg;
    func_001FAFD0(p);
    p->n60 = n;
    p->pvt = D_002D9BE0;
    p->n3B8 = m;
    for (i = 0; i < 6; i++) p->a[i] = 1.0f;
    pg = &D_003DD040;
    SetDirty__4CSndUiUi(p, 0x801, 0x801);
    if (*(pg->a + ItrackFromStream__FP8SOUNDMGRP9SNDSTREAM(pg, p->n60)) == 0.0f) Pause__4CSnd(p);
    if (pg->n58) Pause__4CSnd(p);
    return p;
}
