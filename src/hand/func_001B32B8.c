struct S { int state; char pad[0x4C]; char x50[0x20]; int x70; int x74; int x78; int x7C; int x80; int x84; int x88; int x8C; int x90; int x94; };
int CbDrain(void *a, int b, void *c) asm("CbDrain__10CByteQueueiP12CQueueOutput");
void snd_StartMovieSound(int a, int b, int c, int d, int e);
void func_001B2EB8(void *p);
void func_001B32B8(struct S *p)
{
    switch (p->state) {
    case 2:
        CbDrain(p->x50, p->x94, &p->x70);
        if (p->x94 == 0) {
            if (p->x74 == 0x10) snd_StartMovieSound(p->x84, 0x1000, 0, p->x78, p->x7C);
            else snd_StartMovieSound(p->x84, p->x88, p->x84, 0, 0);
            p->state = 3;
        }
        break;
    case 3:
        func_001B2EB8(&p->x70);
        CbDrain(p->x50, p->x94, &p->x70);
        break;
    }
}
