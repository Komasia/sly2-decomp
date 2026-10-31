/* FValidCdMmode (Sly 1 cd.c): re-read the disc type into g_scecd; DVD media mode is valid for a PS2 DVD. */
#define SCECdPS2DVD 0x14   /* libcdvd disc type */

extern "C" int func_00242AB8(void);   /* the disc type (libcdvd; Sly 1 calls sceCdGetDiskType here) */
extern int g_scecd;

int FValidCdMmode()
{
    int scecd = func_00242AB8();

    if (g_scecd != scecd)
        g_scecd = scecd;

    return g_scecd == SCECdPS2DVD;
}
