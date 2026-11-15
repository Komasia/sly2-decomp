// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceGsSetDefDrawEnv (libgraph): fill the 8 A+D registers of a default draw environment for a w x h buffer.
   Returns the qword count (8). */
typedef unsigned long u_long;
typedef struct { u_long AC:1, pad1:63; } sceGsPrmodecont;
typedef struct { u_long CLAMP:1, pad1:63; } sceGsColclamp;
typedef struct { u_long DTHE:1, pad1:63; } sceGsDthe;
typedef struct {
    u_long frame1, frame1addr;
    u_long zbuf1, zbuf1addr;
    u_long xyoffset1, xyoffset1addr;
    u_long scissor1, scissor1addr;
    sceGsPrmodecont prmodecont; u_long prmodecontaddr;
    sceGsColclamp colclamp; u_long colclampaddr;
    sceGsDthe dthe; u_long dtheaddr;
    u_long test1, test1addr;
} sceGsDrawEnv1;
short sceGszbufaddr(short psm, short w, short h);
#define SET_FRAME(fbp, fbw, psm, fbmsk) ((u_long)(fbp) | ((u_long)(fbw) << 16) | ((u_long)(psm) << 24) | ((u_long)(fbmsk) << 32))
#define SET_ZBUF(zbp, psm, zmsk) ((u_long)(zbp) | ((u_long)(psm) << 24) | ((u_long)(zmsk) << 32))
#define SET_XYOFFSET(ofx, ofy) ((u_long)(ofx) | ((u_long)(ofy) << 32))
#define SET_SCISSOR(x0, x1, y0, y1) ((u_long)(x0) | ((u_long)(x1) << 16) | ((u_long)(y0) << 32) | ((u_long)(y1) << 48))
#define SET_TEST(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u_long)(ate) | ((u_long)(atst) << 1) | ((u_long)(aref) << 4) | ((u_long)(afail) << 12) | \
     ((u_long)(date) << 14) | ((u_long)(datm) << 15) | ((u_long)(zte) << 16) | ((u_long)(ztst) << 17))
int sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm)
{
    draw->frame1addr = 0x4C;        /* FRAME_1 */
    draw->frame1 = SET_FRAME(0, ((w + 63) >> 6) & 0x3F, psm & 0xF, 0);
    draw->zbuf1addr = 0x4E;         /* ZBUF_1; ZMSK when there is no depth test */
    if (ztest == 0)
        draw->zbuf1 = SET_ZBUF(sceGszbufaddr(psm, w, h), zpsm & 0xF, 1);
    else
        draw->zbuf1 = SET_ZBUF(sceGszbufaddr(psm, w, h), zpsm & 0xF, 0);
    draw->xyoffset1addr = 0x18;     /* XYOFFSET_1: centre the w x h area on (2048, 2048) */
    draw->xyoffset1 = SET_XYOFFSET((2048 - (u_long)(short)(w >> 1)) << 4, (2048 - (u_long)(short)(h >> 1)) << 4);
    draw->scissor1addr = 0x40;      /* SCISSOR_1 */
    draw->scissor1 = SET_SCISSOR(0, w - 1, 0, h - 1);
    draw->prmodecontaddr = 0x1A;    /* PRMODECONT */
    draw->prmodecont.AC = 1;
    draw->colclampaddr = 0x46;      /* COLCLAMP */
    draw->colclamp.CLAMP = 1;
    draw->dtheaddr = 0x45;          /* DTHE: dither the 16-bit formats */
    if (psm & 2)
        draw->dthe.DTHE = 1;
    else
        draw->dthe.DTHE = 0;
    draw->test1addr = 0x47;         /* TEST_1 */
    if (ztest)
        draw->test1 = SET_TEST(0, 0, 0, 0, 0, 0, 1, ztest & 3);
    else
        draw->test1 = SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    __asm__ volatile("sync");
    return 8;
}
