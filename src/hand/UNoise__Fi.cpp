float UNoise(int n)
{
    int x = (n << 13) ^ n;
    int y = x * x * 0x3d73 + 0xc0ae5;
    int z = x * y + 0x5208dd0d;
    x = z & 0x7fffffff;
    return (float)x / 2147483648.0f;
}
