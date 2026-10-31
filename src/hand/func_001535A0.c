extern char D_003DD040[];
extern float g_lmZeroOne[2];
struct Q { int pad[3]; float gC; };
struct S { char pad[0x58]; float g58; float g5C; };
float func_001FE3F8(void *p);
static inline float GLerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
float func_001535A0(struct S *p, struct Q *q)
{ float g = func_001FE3F8(D_003DD040); float d;
  if (g < q->gC) { d = (q->gC - g) / p->g58; } else { d = (g - q->gC) / p->g5C; }
  return GLerp(g_lmZeroOne[0], g_lmZeroOne[1], 1.0f - d); }
