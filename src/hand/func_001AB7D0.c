extern char D_002A6BB0[], D_002A6BC8[], D_002A6BF8[];
void *func_001AC748(void *s, char *a);
void *func_001AC900(void *s, char *a, char *b, int n);
void *func_001AC008(void *s, char *a, char *b);
void *func_001AC238(void *s, char *a);
void *func_001AB7D0(void *s)
{
    void *p = func_001AC748(s, D_002A6BB0);
    if (p)
        return p;
    p = func_001AC900(s, D_002A6BC8, D_002A6BF8, 5);
    if (p)
        return p;
    p = func_001AC008(s, D_002A6BB0, D_002A6BF8);
    if (p)
        return p;
    return func_001AC238(s, D_002A6BB0);
}
