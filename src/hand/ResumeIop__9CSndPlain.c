/* CSndPlain::ResumeIop: resume the sound's IOP voice (its handle at +0x40, snd_ContinueSound). */
struct CSndPlain {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int hvoice;   /* the IOP side's handle */
};
void snd_ContinueSound(int hvoice);

// name: SafeHouse port (CSndPlain::ResumeIop)
void ResumeIop__9CSndPlain(struct CSndPlain *psnd)
{
    snd_ContinueSound(psnd->hvoice);
}
