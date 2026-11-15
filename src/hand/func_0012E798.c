/* CPLOOKAT::Activate: the base policy's activate, then the policy remembers its camera object; a camera object
 * with a field of view (+0x130) sets the camera's. Layout: SafeHouse port (cplcy.h CPLOOKAT / CMOBJ). */
extern char g_cm[];
typedef struct CMOBJ { char pad[0x130]; float radFOV; } CMOBJ;   /* field: SafeHouse port (0: keep) */
typedef struct CPLOOKAT { int pad[4]; CMOBJ *pcmobj; } CPLOOKAT;   /* field: SafeHouse port */
void Activate__5CPLCYP2LOPv(CPLOOKAT *pcplcy, void *psoFocus, CMOBJ *pcmobj);
void SetCmFov__FP2CMf(void *pcm, float radFOV);
// name: SafeHouse port (CPLOOKAT::Activate)
void Activate__8CPLOOKATP2LOPv(CPLOOKAT *pcplcy, void *psoFocus, CMOBJ *pcmobj)
{
    Activate__5CPLCYP2LOPv(pcplcy, psoFocus, pcmobj);
    pcplcy->pcmobj = pcmobj;
    if (pcmobj->radFOV != 0.0f)
        SetCmFov__FP2CMf(g_cm, pcmobj->radFOV);
}
