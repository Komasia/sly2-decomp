/* SetCdMmode (Sly 1 cd.c): select DVD media mode when the disc is a PS2 DVD. */
extern "C" int sceCdMmode(int media);

#define SCECdPS2DVD 0x14   /* libcdvd disc type */

extern int g_scecd;        /* disc type from sceCdGetDiskType */

void SetCdMmode()
{
    if (g_scecd == SCECdPS2DVD)
        sceCdMmode(2);
}
