/* CSndPlain::PauseIop: pause the sound's IOP voice (its handle at +0x40, func_002323A8). */
struct CSndPlain {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int hvoice;   /* the IOP side's handle */
};
void func_002323A8(int hvoice);

// name: SafeHouse port (CSndPlain::PauseIop)
void PauseIop__9CSndPlain(struct CSndPlain *psnd)
{
    func_002323A8(psnd->hvoice);
}
