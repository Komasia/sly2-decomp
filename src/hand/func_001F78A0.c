int func_001F78A0(int x)
{
    int i; int m;
    for (i = 0, m = 1; i < 26; i++, m <<= 1) if (x & m) break;
    return i;
}
