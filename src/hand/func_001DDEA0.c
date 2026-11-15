/* class: JOBHELP (a text callback of Job Help's screen object): the title (+0x6C) of the job on row irow, localized. */
struct JOB { char pad[0x6C]; int idTitle; };
struct JOBHELPROW { struct JOB *pjob; int idRow, idDone; };
struct JOBHELP {                      /* D_003DA3C0 (field: SafeHouse port, shop.cpp JOBHELP) */
    /* 0x00 */ char pad[0x48];
    /* 0x48 */ int crow;
    /* 0x4c */ struct JOBHELPROW arow[1];
};
extern struct JOBHELP D_003DA3C0;
extern struct G g_sw;
void *func_0013E368(struct G *psw, int id);   /* a localized text */
void s1_strcpy(void *pchDst, void *pchSrc) asm("strcpy");

void func_001DDEA0(void *pch, int irow)
{
    struct JOBHELP *pjobhelp = &D_003DA3C0;
    if (irow < pjobhelp->crow)
        s1_strcpy(pch, func_0013E368(&g_sw, pjobhelp->arow[irow].pjob->idTitle));
}
