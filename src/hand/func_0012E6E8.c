/* The camera object's OnRemove (vt slot 12; SafeHouse cmworld.cpp EnableCmObject(plo, false)): OnLoRemove, then an
 * enabled camera object revokes its priority-10 camera-object policy (CM +0x4A8). */
extern char g_cm[];   /* g_cm + 0x4A8: the CPLOOKAT policy */
void OnLoRemove__FP2LO(void *plo);
void RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(void *pcm, int n, int cpp, void *pcplcy, void *psoFocus, void *pv);
typedef struct CMOBJ { char pad[0x124]; int fEnabled; } CMOBJ;   /* field: SafeHouse port */
void func_0012E6E8(CMOBJ *pcmobj)
{
    OnLoRemove__FP2LO(pcmobj);
    if (pcmobj->fEnabled)
        RevokeCmPolicy__FP2CMi3CPPP5CPLCYii(g_cm, 15, 10, g_cm + 0x4A8, 0, pcmobj);
}
