/* PsndNewPlain: a new banked sound effect object (CSndPlain, 0x70 bytes) for a world sound id. */
struct CSndPlain;
void *func_001FC0F0(int cb);   /* SafeHouse: the sound objects' allocator */
struct CSndPlain *__9CSndPlaini(void *pv, int sfxid);   /* CSndPlain::CSndPlain(int sfxid) */

// name: SafeHouse port (PsndNewPlain)
struct CSndPlain *PsndNewPlain__Fi(int sfxid)
{
    return __9CSndPlaini(func_001FC0F0(0x70), sfxid);
}
