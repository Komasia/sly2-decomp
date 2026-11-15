/* OnAmbientRegistered (the ambient sound object's vt slot 23, SafeHouse sound.h): the base, then each sound record
 * {sound id, falloff start / end, volume, pitch} starts a plain sound sourced at the object, kept in its handle.
 * Layout: SafeHouse port (soundglue.cpp AMBREC). */
typedef struct SND { int id; float sFalloffMin, sFalloffMax, g, pitch; } SND;   /* field: SafeHouse port */
typedef struct H { void *psnd; } H;
typedef struct AMB { char pad[0xE4]; int csnd; SND *asnd; H *ah; } AMB;      /* field: SafeHouse port */
void func_001A6178(AMB *pamb);
void *PsndNewPlain__Fi(int id);
void SetSource__4CSndPv(void *psnd, AMB *pamb);
void SetFalloff__4CSndff(void *psnd, float sMin, float sMax);
void SetVolume__4CSndf(void *psnd, float g);
void SetPitch__4CSndiif(void *psnd, float pitch);
void func_00258040(H *ph, void *psnd);   /* the handle set */
void func_0012ED20(AMB *pamb)
{
    int isnd;
    func_001A6178(pamb);
    for (isnd = 0; isnd < pamb->csnd; isnd++) {
        SND *prec = &pamb->asnd[isnd];
        void *psnd = PsndNewPlain__Fi(prec->id);
        SetSource__4CSndPv(psnd, pamb);
        SetFalloff__4CSndff(psnd, prec->sFalloffMin, prec->sFalloffMax);
        SetVolume__4CSndf(psnd, prec->g);
        SetPitch__4CSndiif(psnd, prec->pitch);
        func_00258040((H *)(isnd * 4 + (int)pamb->ah), psnd);
    }
}
