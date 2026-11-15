/* The ambient sound object's current sound record (+0xE0): when there is none yet, the next record becomes it and
 * a default one is added (no sound, falloff 300..3000, volume 1, pitch 0). Layout: SafeHouse port (AMBREC). */
typedef struct SND { int a[5]; } SND;
typedef struct AMB { char pad[0xE0]; SND *psndCur; int csnd; SND *asnd; } AMB;
void func_0012EEE0(AMB *pamb, int id, int sFalloffMin, int sFalloffMax, float g, float pitch);
SND *func_0012EE78(AMB *pamb)
{
    if (!pamb->psndCur) {
        pamb->psndCur = &pamb->asnd[pamb->csnd];
        func_0012EEE0(pamb, -1, 300, 3000, 1.0f, 0.0f);
    }
    return pamb->psndCur;
}
