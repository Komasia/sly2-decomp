/* PsndNewPlain: a new banked sound effect object (CSndPlain, 0x70 bytes) for a world sound id. */
struct CSndPlain;
void *func_001FC0F0(int cb);   /* SafeHouse: the sound objects' allocator */
struct CSndPlain *func_001FBBC8(void *pv, int sfxid);   /* SafeHouse: CSndPlain::CSndPlain(int sfxid) */

// name: SafeHouse port (PsndNewPlain)
struct CSndPlain *PsndNewPlain__Fi(int sfxid)
{
    return func_001FBBC8(func_001FC0F0(0x70), sfxid);
}
