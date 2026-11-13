/* InitHudWidgets (after a world load): the HUD widgets find their screen objects: the health / gadget power gauge
 * (D_003D9E80), the menu D_003D9ED0 (0x1AE928), the dialog subtitle object (D_002E1E60, 0x1A3020), the counters and
 * prompts (0x1DA770 on D_003DA0F0, D_003DA150, D_002E65A0, D_003DA530), the prompt D_003DA0C0 (0x1DA2E0), and
 * D_003DA3C0 (0x1DCCA0), D_002E6550 (0x1ACAE8), D_003DA4F0 (0x1DD690). Source: SafeHouse port (hudwidget.h). */
extern char D_002E1E60[];
extern char D_002E6550[];
extern char D_002E65A0[];
extern char D_003D9E80[];
extern char D_003D9ED0[];
extern char D_003DA0C0[];
extern char D_003DA0F0[];
extern char D_003DA150[];
extern char D_003DA3C0[];
extern char D_003DA4F0[];
extern char D_003DA530[];
void InitGauge__FP5GAUGE(void *pgauge);
void func_001AE928(void *pv);   /* SafeHouse: InitMenu */
void func_001A3020(void *pv);
void func_001DA770(void *pv);
void func_001DA2E0(void *pv);
void func_001DCCA0(void *pv);
void func_001ACAE8(void *pv);
void func_001DD690(void *pv);

// name: SafeHouse port (InitHudWidgets, hudwidget.h)
void InitHudWidgets__FP2SW(void)
{
    InitGauge__FP5GAUGE(D_003D9E80);
    func_001AE928(D_003D9ED0);
    func_001A3020(D_002E1E60);
    func_001DA770(D_003DA0F0);
    func_001DA770(D_003DA150);
    func_001DA2E0(D_003DA0C0);
    func_001DCCA0(D_003DA3C0);
    func_001ACAE8(D_002E6550);
    func_001DA770(D_002E65A0);
    func_001DD690(D_003DA4F0);
    func_001DA770(D_003DA530);
}
