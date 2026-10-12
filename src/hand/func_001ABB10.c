struct SAVE { char ab[0x5464]; };
struct M { char pad[0x24]; struct SAVE asave[4]; };
extern char D_002A6C50[], D_002A6C60[], D_002A6C78[];
int func_0021ECD8(char *buf, char *fmt, ...);
void func_001ABB10(struct M *pm, struct SAVE *ps, char *buf)
{
    func_0021ECD8(buf, D_002A6C50, D_002A6C60, D_002A6C78, ps - pm->asave + 1);
}
