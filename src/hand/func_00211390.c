/* A screen string generator (beside 0x2113B8, SafeHouse screenrt.cpp): the dialog's subtitle text of D_004435F0. */
struct DIALOGSUB;
extern struct DIALOGSUB D_004435F0;   /* the subtitle state */
void GetDialogSubtitleText__FP9DIALOGSUBPc(struct DIALOGSUB *psub, char *pch);

void func_00211390(char *pch)
{
    GetDialogSubtitleText__FP9DIALOGSUBPc(&D_004435F0, pch);
}
