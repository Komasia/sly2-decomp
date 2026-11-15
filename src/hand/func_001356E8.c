/* FireBentleyDart (the aim): the line from the camera's screen centre at depth 10 (D_002BC970) to 40000 deep
 * (D_002BC980); the point the dart aims at (+0x16F0) is the nearest solid object it meets (not Bentley's own, by his
 * collision entries +0xEC), else the far end. Layout: SafeHouse port (gang.cpp FireBentleyDart). */
typedef int ti128 __attribute__((mode(TI)));
struct STACKSCOPE { int a[4]; };
struct LSG { ti128 pos; int pad[0x14]; };
struct BENTLEY { char pad[0xec]; int poxa; char pad2[0x16f0 - 0xf0]; ti128 posDartAim; };
extern ti128 D_002BC970;
extern ti128 D_002BC980;
extern char g_cm[];
extern char g_sw[];
ti128 ConvertCmScreenToWorld__FP2CMG9VU_VECTOR(void *pcm, ti128 pos);
struct STACKSCOPE *__10STACKSCOPE(struct STACKSCOPE *pss);
void _$_10STACKSCOPE(struct STACKSCOPE *pss, int n);
void func_0020FA10();   /* the filter: solid entries */
void func_0020FAA0(void *psw, ti128 posA, ti128 posB, void (*pfnFilter)(), int poxaSkip, int *cpso, int *apso);
int PsoHitTestLineObjects(int n, ti128 posA, ti128 posB, int cpso, int apso, struct LSG *plsg) asm("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
// name: SafeHouse port (FireBentleyDart)
void FireBentleyDart__FP7BENTLEY(struct BENTLEY *pbentley)
{
    struct STACKSCOPE ss;
    struct LSG lsg;
    int cpso;
    int apso;
    ti128 posNear = ConvertCmScreenToWorld__FP2CMG9VU_VECTOR(g_cm, D_002BC970);
    ti128 posFar = ConvertCmScreenToWorld__FP2CMG9VU_VECTOR(g_cm, D_002BC980);
    __10STACKSCOPE(&ss);
    func_0020FAA0(g_sw, posNear, posFar, func_0020FA10, pbentley->poxa, &cpso, &apso);
    if (PsoHitTestLineObjects(1, posNear, posFar, cpso, apso, &lsg))
        pbentley->posDartAim = lsg.pos;
    else
        pbentley->posDartAim = posFar;
    _$_10STACKSCOPE(&ss, 2);
}
