struct G { int a; };
extern struct G g_sw;
struct P { char pad[0x38]; int fOn; int id; };
void ResumeGame__FP9GAMEPAUSEi(struct G *pg, int id);
void ResumeTalk__FP2SW(struct G *pg);
void PauseGame__FP9GAMEPAUSEi(struct G *pg, int id);
void PauseTalk__FP2SW(struct G *pg);
void func_001E50E0(struct P *p, int fOn, int id)
{
if (!fOn) { if (!p->fOn) return; } else { if (p->fOn) { if (id == p->id) return; ResumeGame__FP9GAMEPAUSEi(&g_sw, p->id); ResumeTalk__FP2SW(&g_sw); } PauseGame__FP9GAMEPAUSEi(&g_sw, id); PauseTalk__FP2SW(&g_sw); p->fOn = fOn; p->id = id; return; } ResumeGame__FP9GAMEPAUSEi(&g_sw, p->id); ResumeTalk__FP2SW(&g_sw); p->fOn = fOn; p->id = id;
}
