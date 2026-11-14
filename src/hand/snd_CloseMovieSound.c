/* snd_CloseMovieSound (0x232F60; 989snd): the same body as Sly 1's 989snd.c snd_CloseMovieSound - the IOP command 0x3C with no data,
 * waited for (0x2325E0, Sly 1 snd_SendIOPCommandAndWait). */
// name: Sly 1 (snd_CloseMovieSound, 989snd.c; same command number and body)
unsigned int func_002325E0(int command, int cbData, char *pbData);   /* Sly 1 snd_SendIOPCommandAndWait */

void snd_CloseMovieSound(void)
{
    func_002325E0(0x3C, 0, 0);
}
