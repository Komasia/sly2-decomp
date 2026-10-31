extern char g_game[];
void func_00161F10(void *pq, void *a, int n, void *b, int c, int d);
void func_00228920(char *p, int c, int d)
{
    func_00161F10(g_game, p + 0x124 + 4, 4, p + 0x124, c, d);
}
