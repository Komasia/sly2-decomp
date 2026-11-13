struct E { int f0; int f4; char pad[0x20]; };
extern struct E D_002AC880[];
int S16Read(void *) asm("S16Read__18CBinaryInputStream");
void LoadOptionFromBrx__FPvP5EOPIDiP18CBinaryInputStream(void *, struct E *, int, void *);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(void *p, void *pbis) {
    int n;
    while ((n = S16Read(pbis)) >= 0) {
        struct E *pe = &D_002AC880[n];
        LoadOptionFromBrx__FPvP5EOPIDiP18CBinaryInputStream(p, pe, pe->f4 & 0x2580, pbis);
    }
}
