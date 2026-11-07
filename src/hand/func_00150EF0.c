typedef int qword __attribute__((mode(TI)));
struct S {
    int pad[6]; float g18; int pad1c;
    qword q20; qword q30; qword q40; qword q50; qword q60; float g70; int pad74[3];
    qword q80; qword q90; float gA0; int padA4[2]; float gAC;
};
qword PosFocus__6CPFREE(struct S *p);
qword PosEye__6CPFREE(struct S *p);
// name: SafeHouse port (CPFREE::Snap)
void Snap__6CPFREE(struct S *p)
{
    p->q20 = PosFocus__6CPFREE(p);
    p->q30 = PosEye__6CPFREE(p);
    if (0.0f <= p->g18)
        p->gAC = p->g18;
    p->q50 = p->q80;
    p->q60 = p->q90;
    p->g70 = p->gA0;
}
