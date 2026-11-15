struct SCRPOS { char pad[0x14]; float y; };   /* the screen object's placement: its offset */
struct SCREENRT { char pad[0xF8]; struct SCRPOS *ppos; };
/* a stacked HUD counter: its screen object, the offset's speed, whether it was hidden */
struct COUNTER { struct SCREENRT *pscr; float dy; int fHidden; };
struct SW { char pad[0x3BA0]; struct COUNTER acounter[4]; char pad2[0x476C - 0x3BD0]; float tTimerEnd; int sTimerLast; };
extern struct { float t; float dt; } g_clock;
extern char D_002C3E88[];   /* the offsets' smoothing */
extern float D_002C3E80;   /* the space between counters */
int FVisible__FP8SCREENRT(struct SCREENRT *pscr);
float GSmoothA(float gCur, float dgCur, float gTarget, void *psmpa, float *pdgNext, float dt) asm("GSmoothA__FffffP4SMPAPf");
void *PsndNewPlain__Fi(int sfx);
void SetSource__4CSndPv(void *psnd, void *pvSource);

/* StackCounters (0x20F7E0): the visible HUD counters are stacked one below the other (their offsets smoothed into
 * place; a counter shown again starts in place); with the last one, each second of the timer left ticks a sound
 * (0x30 / 0x31 alternately). */
// name: SafeHouse port (StackCounters)
void StackCounters__FP2SW(struct SW *psw)
{
    float yZero;
    float y = 0.0f;
    int i;
    yZero = y;
    for (i = 0; i < 4; i++) {
        struct COUNTER *pcounter = &psw->acounter[i];
        struct SCREENRT *pscr = pcounter->pscr;
        if (!pscr || !FVisible__FP8SCREENRT(pscr)) {
            pcounter->fHidden = 1;
            continue;
        }
        if (pcounter->fHidden) {
            pscr->ppos->y = y;
            pcounter->dy = 0.0f;
            pcounter->fHidden = 0;
        } else {
            pscr->ppos->y = GSmoothA(pscr->ppos->y, pcounter->dy, y, D_002C3E88, &pcounter->dy, g_clock.dt);
        }
        y += D_002C3E80;
        if (i == 3) {
            float dt = -g_clock.t + psw->tTimerEnd;
            int s;
            dt = (0.0f > dt) ? 0.0f : dt;
            s = (int)dt;
            if (s != psw->sTimerLast) {
                SetSource__4CSndPv(PsndNewPlain__Fi((s & 1) ? 0x30 : 0x31), 0);
                psw->sTimerLast = s;
            }
        }
    }
}
