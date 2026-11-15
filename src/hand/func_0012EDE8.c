/* OnAmbientUnregistered (vt slot 22): the base, then each playing ambient sound stops at once and its handle is
 * cleared. Layout: SafeHouse port (soundglue.cpp AMBREC). */
typedef struct AMB { char pad[0xE4]; int csnd; int pad2; void **ah; } AMB;   /* field: SafeHouse port */
void func_001A6150(AMB *pamb);
void Stop__4CSndf(void *psnd, float dtFade);
void func_00258040(void **ph, int n);   /* the handle set */
// name: SafeHouse port (OnAmbientUnregistered)
void OnAmbientUnregistered__FP2LO(AMB *pamb)
{
    int isnd;
    func_001A6150(pamb);
    for (isnd = 0; isnd < pamb->csnd; isnd++) {
        void **ph = (void **)((isnd << 2) + (int)pamb->ah);
        if (ph && *ph) {
            Stop__4CSndf(*ph, 0.0f);
            func_00258040(ph, 0);
        }
    }
}
