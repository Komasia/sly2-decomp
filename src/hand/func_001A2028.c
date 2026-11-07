struct K { int a, b; };
extern struct K D_002A6790;
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void func_001A0B40(void *p, int n);
void func_001A15B0(void *p, struct K k);
void func_001A2028(void *p)
{
    SetSource__4CSndPv(PsndNewPlain__Fi(0x6A), 0);
    func_001A0B40(p, 6);
    func_001A15B0(p, D_002A6790);
}
