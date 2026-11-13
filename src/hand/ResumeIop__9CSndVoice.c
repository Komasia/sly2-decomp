/* CSndVoice::ResumeIop: a streamed sound's 'ResumeIop' sent to the IOP (SpiopContinue: spiop request 'SUKR' 4 on the handle +0x40).
 * Layout: SafeHouse port (sound.h CSnd). */
struct CSndVoice {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ unsigned int m_h;   /* field: SafeHouse port - the spiop id */
};
/* SafeHouse: the spiop RPC request (id 'SUKR', function, then up to five arguments) */
void func_00233088(int id, int fn, int a2, int a3, int a4, int a5, int a6);

// name: SafeHouse port (CSndVoice::ResumeIop)
void ResumeIop__9CSndVoice(struct CSndVoice *psnd)
{
    func_00233088(0x524B5553, 4, psnd->m_h, 0, 0, 0, 0);
}
