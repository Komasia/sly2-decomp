/* OnZoneUnregistered: a zone left the world: its base handling (func_001A6150), then its camera is turned off. */
struct LO;
void func_001A6150(struct LO *plo);
void UpdateZoneCamera(struct LO *plo, int fOn) asm("UpdateZoneCamera__FP2LOi");

// name: SafeHouse port (OnZoneUnregistered)
void OnZoneUnregistered__FP2LO(struct LO *plo)
{
    func_001A6150(plo);
    UpdateZoneCamera(plo, 0);
}
