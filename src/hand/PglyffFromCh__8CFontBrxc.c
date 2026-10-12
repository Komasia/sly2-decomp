struct CFontBrx { char pad[0x20]; int c; unsigned int *ach; };
int PglyffFromCh__8CFontBrxc(struct CFontBrx *p, unsigned char ch)
{
    int lo = 0;
    int hi = p->c - 1;
    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        int d = ch - p->ach[mid];
        if (d == 0)
            return mid + 1;
        if (d > 0)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}
