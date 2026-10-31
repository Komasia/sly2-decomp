/* FCdCompleted (Sly 1 cd.c): has the disc read finished? fBlock waits for it. Sly 2 calls sceCdSync directly
 * (Sly 1 went through snd_StreamSafeCdSync). */
extern "C" int sceCdSync(int mode);

int FCdCompleted(int fBlock)
{
    return sceCdSync(!fBlock) == 0;
}
