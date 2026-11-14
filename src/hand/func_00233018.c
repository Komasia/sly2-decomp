/* 989snd (called by 0x1B2EB8, the movie player): the IOP command 0x5B with no data, waited for (0x2325E0, Sly 1
 * snd_SendIOPCommandAndWait); its answer is the movie sound's position (Sly 1 has no command 0x5B). */
unsigned int snd_SendIOPCommandAndWait__FiiPc(int command, int cbData, char *pbData);

unsigned int func_00233018(void)
{
    return snd_SendIOPCommandAndWait__FiiPc(0x5B, 0, 0);
}
