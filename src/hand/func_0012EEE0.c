/* The ambient sound object's EOPID 99 option (SafeHouse soundglue.cpp: 0x101768 -> 0x12EEE0): one more sound record
 * {sound id, falloff start / end, volume, pitch}, 8 at most. */
typedef struct SND { int id; float sFalloffMin; float sFalloffMax; float g; float pitch; } SND;   /* field: SafeHouse port */
typedef struct AMB { char pad[0xE4]; int csnd; SND *asnd; } AMB;
#define CSND_AMB_MAX 8
void func_0012EEE0(AMB *pamb, int id, int sFalloffMin, int sFalloffMax, float g, float pitch)
{
    if (pamb->csnd < CSND_AMB_MAX) {
        SND *psnd = &pamb->asnd[pamb->csnd++];
        psnd->id = id;
        psnd->sFalloffMin = sFalloffMin;
        psnd->sFalloffMax = sFalloffMax;
        psnd->g = g;
        psnd->pitch = pitch;
    }
}
