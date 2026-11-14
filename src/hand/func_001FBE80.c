struct A { char pad[0x40]; int h; char pad2[4]; float g; };
void snd_AutoVol(int h, int a, int b, int c);
void snd_StopSound(int h);
// name: SafeHouse port (CSndPlain::StopIop)
void StopIop__9CSndPlain(struct A *p)
{
    if (p->g > 0.0f)
        snd_AutoVol(p->h, -4, (int)(p->g * 240.0f), 2);
    else
        snd_StopSound(p->h);
}
