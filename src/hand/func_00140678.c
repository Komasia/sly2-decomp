struct X { char pad[0x10DC]; int b; int pad2; int a; int d; int c; };
void StopNearestLaunchTracking__FP5ACTOR(struct X *p, int a, int b, int c, int d);
// name: SafeHouse port (SetActorTargets)
void SetActorTargets__FP5ACTORiiii(struct X *p, int a, int b, int c, int d)
{
    if (b != p->b) StopNearestLaunchTracking__FP5ACTOR(p, a, b, c, d);
    p->b = b;
    p->a = a;
    p->d = d;
    p->c = c;
}
