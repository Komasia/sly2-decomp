/* CSndPlain::PauseIop: pause the sound's IOP voice (its handle at +0x40, snd_PauseSound). */
struct CSndPlain {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int hvoice;   /* the IOP side's handle */
};
void snd_PauseSound(int hvoice);

// name: SafeHouse port (CSndPlain::PauseIop)
void PauseIop__9CSndPlain(struct CSndPlain *psnd)
{
    snd_PauseSound(psnd->hvoice);
}
