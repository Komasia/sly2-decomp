struct CLOCK { float t; };
extern struct CLOCK g_clock;
float GRandInRange__Fff(float a, float b);
struct X { char pad[0x1138]; float a0, b0, a1, b1; int f; float tNext; };
// name: SafeHouse port (ActorNextLookTime 0x142880)
void ActorNextLookTime(struct X *p) asm("ActorNextLookTime__FP5ACTOR");
void ActorNextLookTime(struct X *p)
{
    float t;
    if (p->f) {
        t = g_clock.t;
        t += GRandInRange__Fff(p->a0, p->b0);
        p->tNext = t;
    } else {
        t = g_clock.t;
        t += GRandInRange__Fff(p->a1, p->b1);
        p->tNext = t;
    }
}
