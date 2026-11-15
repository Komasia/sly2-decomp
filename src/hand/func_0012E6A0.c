/* EnableCmObject (the camera object's OnAdd, vt slot 11): OnLoAdd, then an enabled camera object puts the
 * camera-object policy (CM +0x4A8, CPLOOKAT) on the camera with priority 10. SafeHouse port (cmworld.cpp). */
extern char g_cm[];   /* g_cm + 0x4A8: the CPLOOKAT policy */
void OnLoAdd__FP2LO(void *plo);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *pcm, int cpp, void *pcplcy, void *psoFocus, void *pv);
typedef struct CMOBJ { char pad[0x124]; int fEnabled; } CMOBJ;   /* field: SafeHouse port */
// name: SafeHouse port (EnableCmObject)
void EnableCmObject__FP2LO(CMOBJ *pcmobj)
{
    OnLoAdd__FP2LO(pcmobj);
    if (pcmobj->fEnabled)
        SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, 10, g_cm + 0x4A8, 0, pcmobj);
}
