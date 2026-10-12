char *func_0021EDF8(char *p, int ch)
{
    do {
        if (*(unsigned char *)p == ch)
            return p;
    } while (*p++);
    return 0;
}
