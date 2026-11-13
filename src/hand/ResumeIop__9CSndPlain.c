/* CSndPlain::ResumeIop: resume the sound's IOP voice (its handle at +0x40, func_002323D8). */
struct CSndPlain {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ int hvoice;   /* the IOP side's handle */
};
void func_002323D8(int hvoice);

// name: SafeHouse port (CSndPlain::ResumeIop)
void ResumeIop__9CSndPlain(struct CSndPlain *psnd)
{
    func_002323D8(psnd->hvoice);
}
