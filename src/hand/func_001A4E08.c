/* func_001A4E08 (0x1A4E08): starts the boot sequence (SafeHouse frontend.cpp StartBootSequence): an empty action
 * queue, then the logo movie (D_002A3868), the memory card check (kind 5) and the boot world (D_002A38A8, world id 93)
 * at oid 0x189 with the request flags 1; then runs the first action. */
#include "h5_frontq.h"
#define OID_BOOT_WARP 0x189
extern char g_pbLogoMovie[] __asm__("D_002A3868");
extern char g_pbBootWorld[] __asm__("D_002A38A8");
void func_001A5020(struct ACTIONQ *pq, void *pbMovie);
void func_001A50F8(struct ACTIONQ *pq);
void func_001A5078(struct ACTIONQ *pq, void *pbWorld, int oid, int grf);
void func_001A4E80(struct ACTIONQ *pq);
void func_001A4E08(struct ACTIONQ *pq)
{
    pq->cact = 0;
    pq->iact = 0;
    func_001A5020(pq, g_pbLogoMovie);
    func_001A50F8(pq);
    func_001A5078(pq, g_pbBootWorld, OID_BOOT_WARP, 1);
    func_001A4E80(pq);
}
