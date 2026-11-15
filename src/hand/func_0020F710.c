extern char g_sw[];
extern int D_002C3E70[4];   /* the counters' oids */
/* the counters' setup: two scales of 1 */
struct COUNTERSETUP { float uA; int unk_0x04; int unk_0x08; float uB; int an[4]; };
/* a stacked HUD counter: its screen object */
struct COUNTER { int pscr; int pad[2]; };
struct SW { char pad[0x3BA0]; struct COUNTER acounter[4]; char pad2[0x4764 - 0x3BD0]; int cClueFound; int cClue; };
void *s1_memset(void *pv, int c, int cb) asm("memset");
int PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, int oid, int ploNear);
void func_00213C68(int pscr, struct COUNTERSETUP *psetup);
int func_001C7D08(void);
int func_001C7D00(void);
/* func_0020F710 (0x20F710): the world's four stacked HUD counters found (D_002C3E70) and set up (0x213C68), and
 * the clue bottles found and in all (0x1C7D08 / 0x1C7D00). */
void func_0020F710(struct SW *psw)
{
    struct COUNTERSETUP setup;
    int i;
    int *pn = D_002C3E70;
    s1_memset(&setup, 0, sizeof(setup));
    setup.uB = 1.0f;
    setup.uA = 1.0f;
    for (i = 0; i < 4; i++) {
        int pscr = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x405, D_002C3E70[i], 0);
        if (pscr) {
            func_00213C68(pscr, &setup);
            psw->acounter[i].pscr = pscr;
        }
    }
    psw->cClueFound = func_001C7D08();
    psw->cClue = func_001C7D00();
}
