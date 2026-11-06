struct A; struct B;
struct X {
    static void *operator new(unsigned int cb);
    X(A *pa, B *pb);
    char pad[0x3C0];
};
// name: SafeHouse port (PsndNewVoice)
extern "C" X *PsndNewVoice__FP9SNDSTREAMPv(A *pa, B *pb)
{
    X *px;
    if (pa)
        px = new X(pa, pb);
    else
        px = 0;
    return px;
}
