struct Q { char pad[0x10]; struct Q *next; };
extern int D_002C42E8[4];
int func_00132B10(struct Q *q, int a);
int func_00224508(void *p, struct Q *q)
{
    unsigned i;
    for (; q; q = q->next) {
        for (i = 0; i < 4; i++)
            if (func_00132B10(q, D_002C42E8[i])) return 0;
    }
    return 1;
}
