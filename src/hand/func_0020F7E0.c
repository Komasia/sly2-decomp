struct F8 { char pad[0x14]; float v; };
struct O { char pad[0xF8]; struct F8 *pf8; };
struct E { struct O *po; float v; int f; };
struct S { char pad[0x3BA0]; struct E ae[4]; char pad2[0x476C - 0x3BD0]; float t476C; int n4770; };
extern struct { float t; float dt; } g_clock;
extern char D_002C3E88[];
extern float D_002C3E80;
int FVisible__FP8SCREENRT(struct O *po);
float GSmoothA(float a, float b, float c, void *p, float *pv, float dt) asm("GSmoothA__FffffP4SMPAPf");
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, void *source);

// name: SafeHouse port (StackCounters)
void StackCounters__FP2SW(struct S *p)
{
    float z;
    float t = 0.0f;
    int i;
    z = t;
    for (i = 0; i < 4; i++) {
        struct E *e = &p->ae[i];
        struct O *o = e->po;
        if (!o || !FVisible__FP8SCREENRT(o)) {
            e->f = 1;
            continue;
        }
        if (e->f) {
            o->pf8->v = t;
            e->v = 0.0f;
            e->f = 0;
        } else {
            o->pf8->v = GSmoothA(o->pf8->v, e->v, t, D_002C3E88, &e->v, g_clock.dt);
        }
        t += D_002C3E80;
        if (i == 3) {
            float d = -g_clock.t + p->t476C;
            int n;
            d = (0.0f > d) ? 0.0f : d;
            n = (int)d;
            if (n != p->n4770) {
                SetSource__4CSndPv(PsndNewPlain__Fi((n & 1) ? 0x30 : 0x31), 0);
                p->n4770 = n;
            }
        }
    }
}
