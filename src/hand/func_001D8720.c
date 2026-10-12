struct E { unsigned int h; char *s; int n; struct E *next; };
struct S { struct E *ap[0x35]; int c; struct E *ae; };
unsigned int func_001D8640(char *s);
int func_002342D0(char *a, char *b);
int func_001D8720(struct S *p, char *s)
{
    unsigned int h = func_001D8640(s);
    struct E *pe;
    for (pe = p->ap[h % 0x35]; pe; pe = pe->next) {
        if (pe->h == h && func_002342D0(pe->s, s) == 0)
            return pe->n;
    }
    return -1;
}
