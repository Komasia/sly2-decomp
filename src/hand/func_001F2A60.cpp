typedef unsigned long ulong;
struct A { char pad[0x28]; ulong lo : 60; ulong b60 : 1; ulong hi : 3; };
struct B { char pad[0x10]; ulong lo : 50; ulong b50 : 1; ulong hi : 13; };
extern "C" void func_001F2870(A *, B *);
extern "C" void func_001F2A60(A *pa, B *pb)
{
    if (pb->b50) { pb->b50 = 0;
    bool f = pa->b60; if (f) func_001F2870(pa, pb); }
}
