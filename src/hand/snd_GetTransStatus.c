/* snd_GetTransStatus (0x232FC0; 989snd): the same body as Sly 1's 989snd.c snd_GetTransStatus - the IOP command 0x40 with no data,
 * waited for (0x2325E0, Sly 1 snd_SendIOPCommandAndWait). */
// name: Sly 1 (snd_GetTransStatus, 989snd.c; same command number and body)
unsigned int snd_SendIOPCommandAndWait__FiiPc(int command, int cbData, char *pbData);   /* Sly 1 snd_SendIOPCommandAndWait */

unsigned int snd_GetTransStatus(void)
{
    return snd_SendIOPCommandAndWait__FiiPc(0x40, 0, 0);
}
