/* StartupBlips (0x138FC0): an entry of the startup table 0x2BFCE0; the same body as Sly 1's blip.c StartupBlips:
 * the blips' two GIF packet templates built (BuildBlipAqwGifs 0x138F08: 1 normal, 2 clamped add). */
// name: Sly 1 (StartupBlips__Fv, blip.c; same body, in the blip module 0x138F08..0x139DC0)
typedef struct QW { int an[4]; } QW;

void func_00138F08(int n, QW *aqw);   /* Sly 1 BuildBlipAqwGifs */
extern QW D_002DD5C0[];   /* Sly 1 g_aqwBlipeGifsNormal */
extern QW D_002DD600[];   /* Sly 1 g_aqwBlipeGifsClampedAdd */

void StartupBlips__Fv(void)
{
    func_00138F08(1, D_002DD5C0);
    func_00138F08(2, D_002DD600);
}
