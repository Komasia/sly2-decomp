/* func_0014C2D8 (called by StartupJoy): the cheat codes (Sly 1 joy.h CODE, 0x38-byte records 0x2BD4E0..0x2BD7F0)
 * - the list's entry offset set to 0x18 (0x11A050), then the 15 codes added (0x14BEA8, Sly 1 AddCode). */
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct CODE { char ab[0x38]; } CODE;

void func_0011A050(DL *pdl, int ibDle);
int func_0014BEA8(DL *pdl, CODE *pcode);
extern CODE D_002BD4E0;
extern CODE D_002BD518;
extern CODE D_002BD550;
extern CODE D_002BD588;
extern CODE D_002BD5C0;
extern CODE D_002BD5F8;
extern CODE D_002BD630;
extern CODE D_002BD668;
extern CODE D_002BD6A0;
extern CODE D_002BD6D8;
extern CODE D_002BD710;
extern CODE D_002BD748;
extern CODE D_002BD780;
extern CODE D_002BD7B8;
extern CODE D_002BD7F0;

void func_0014C2D8(DL *pdlCode)
{
    func_0011A050(pdlCode, 0x18);
    func_0014BEA8(pdlCode, &D_002BD4E0);
    func_0014BEA8(pdlCode, &D_002BD518);
    func_0014BEA8(pdlCode, &D_002BD550);
    func_0014BEA8(pdlCode, &D_002BD588);
    func_0014BEA8(pdlCode, &D_002BD5C0);
    func_0014BEA8(pdlCode, &D_002BD5F8);
    func_0014BEA8(pdlCode, &D_002BD630);
    func_0014BEA8(pdlCode, &D_002BD668);
    func_0014BEA8(pdlCode, &D_002BD6A0);
    func_0014BEA8(pdlCode, &D_002BD6D8);
    func_0014BEA8(pdlCode, &D_002BD710);
    func_0014BEA8(pdlCode, &D_002BD748);
    func_0014BEA8(pdlCode, &D_002BD780);
    func_0014BEA8(pdlCode, &D_002BD7B8);
    func_0014BEA8(pdlCode, &D_002BD7F0);
}
