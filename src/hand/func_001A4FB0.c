struct E { int k; int a[6]; };
struct L { unsigned int c; struct E ae[16]; };
extern struct E D_002E1E68;
void func_002333B4(void *, int, int);
struct E *func_001A4FB0(struct L *pl, int k)
{
    struct E *pe;
    if (pl->c >= 16)
        return &D_002E1E68;
    pe = &pl->ae[pl->c++];
    func_002333B4(pe, 0, sizeof(struct E));
    pe->k = k;
    return pe;
}
