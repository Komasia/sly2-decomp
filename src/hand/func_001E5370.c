/* func_001E5370: the script lets go of its animation: retracts and releases its ASEGA (vt slot 2) and ends the
 * actor's script animation. */
#include "relay.h"
struct ASEGA { char pad[0xC]; VTENT *vt; };
void RetractAsega__FP5ASEGA(struct ASEGA *pasega);
void EndActorScriptAnim__FP5ACTOR(void *pactor);
void func_001E5370(JSG *pjsg)
{
    if (pjsg->pasegaCur) {
        RetractAsega__FP5ASEGA(pjsg->pasegaCur);
        { struct ASEGA *pasega = pjsg->pasegaCur; ((void (*)(void *))pasega->vt[2].pfn)(VT_THIS(pasega, &pasega->vt[2])); }
        pjsg->pasegaCur = 0;
    }
    if (pjsg->pstepAseg) {
        EndActorScriptAnim__FP5ACTOR(pjsg->pstepAseg);
        pjsg->pstepAseg = 0;
    }
}
