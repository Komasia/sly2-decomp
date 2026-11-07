typedef int qword __attribute__((mode(TI)));
extern struct { float t; float dt; } g_clock;
extern char g_cm[];
typedef struct { qword a; qword b; } Q2;
typedef struct {
    char pad0[0x14];
    float x14;
    float x18;
    char pad1c[0x70 - 0x1C];
    qword x70;
    qword x80;
    qword x90;
    char pada0[0xF0 - 0xA0];
    Q2 *xF0;
    char padf4[0x100 - 0xF4];
    qword x100;
} OBJ;
void Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(float, float, float, qword, qword, qword, qword, qword *, qword *, int);
qword ConvertCmScreenToWorld__FP2CMG9VU_VECTOR(void *, qword);
static inline float GMax(float a, float b) { return a < b ? b : a; }
// name: SafeHouse port (MoveRipHud)
void MoveRipHud__FP4RIPN(OBJ *p)
{
    Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27(GMax(p->x14 + p->x18 - g_clock.t, g_clock.dt), g_clock.dt, 1.0f, p->x100, p->x90, p->xF0->a, p->xF0->b, &p->x100, &p->x90, 0);
    p->x80 = p->x70;
    p->x70 = ConvertCmScreenToWorld__FP2CMG9VU_VECTOR(g_cm, p->x100);
}
