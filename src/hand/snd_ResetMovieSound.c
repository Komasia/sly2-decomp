/* snd_ResetMovieSound (0x232F28; 989snd): the same body as Sly 1's 989snd.c snd_ResetMovieSound - the IOP command 0x3D with no data,
 * waited for (0x2325E0, Sly 1 snd_SendIOPCommandAndWait). */
// name: Sly 1 (snd_ResetMovieSound, 989snd.c; same command number and body)
unsigned int snd_SendIOPCommandAndWait__FiiPc(int command, int cbData, char *pbData);   /* Sly 1 snd_SendIOPCommandAndWait */

void snd_ResetMovieSound(void)
{
    snd_SendIOPCommandAndWait__FiiPc(0x3D, 0, 0);
}
