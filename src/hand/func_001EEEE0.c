struct L { int x; int c; void *a[1]; };
int func_00132B10(void *p, void *key);
void *func_001EEEE0(struct L *pl, void *key)
{
    int i;
    for (i = 0; i < pl->c; i++) {
        void *p = pl->a[i];
        if (func_00132B10(p, key)) return p;
    }
    return 0;
}
