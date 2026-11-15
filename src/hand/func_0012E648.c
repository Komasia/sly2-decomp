/* The camera object's (cid 0x2C) post-load: PostLoLoad, then it is enabled (+0x124); an object already in the world
 * (LO +0x28 bit 60) puts the camera-object policy (CM +0x4A8, CPLOOKAT) on the camera with priority 10.
 * Layout: SafeHouse port (cplcy.h CMOBJ, cmworld.cpp EnableCmObject). */
extern char g_cm[];   /* g_cm + 0x4A8: the CPLOOKAT policy */
void PostLoLoad__FP2LO(void *plo);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *pcm, int cpp, void *pcplcy, void *psoFocus, void *pv);
typedef struct CMOBJ {
    char pad[0x28];
    unsigned long grf;      /* LO +0x28 flag bits (60: in the world) */
    char pad2[0x124 - 0x30];
    int fEnabled;           /* field: SafeHouse port (cmworld.cpp CMSTATE fEnabled) */
} CMOBJ;
void func_0012E648(CMOBJ *pcmobj)
{
    PostLoLoad__FP2LO(pcmobj);
    pcmobj->fEnabled = 1;
    if ((int)(pcmobj->grf >> 60) & 1)
        SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, 10, g_cm + 0x4A8, 0, pcmobj);
}
