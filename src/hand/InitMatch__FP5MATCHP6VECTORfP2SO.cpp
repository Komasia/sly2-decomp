typedef int qword __attribute__((mode(TI)));
struct VECTOR;
struct SO;
struct MATCH { char pad[0x20]; float g20; float g24; int n28; int pad2; qword q30; };
extern qword g_clqOne;
extern "C" void func_001CE920(MATCH *p, VECTOR *pv, float g, SO *pso);
void InitMatch(MATCH *pmatch, VECTOR *pv, float g, SO *pso)
{
    func_001CE920(pmatch, pv, g, pso);
    pmatch->q30 = g_clqOne;
    pmatch->g20 = g;
    pmatch->g24 = 1.0f - g;
    pmatch->n28 = 0;
}
