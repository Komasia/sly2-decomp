struct E { unsigned int h; char *s; void *pv; struct E *next; };
struct S { struct E *ap[0x35]; int c; struct E *ae; };
unsigned int func_001D8640(char *s);
void func_001D8690(struct S *p, char *s, void *pv) {
    unsigned int h = func_001D8640(s);
    unsigned int ih = h % 0x35;
    struct E *pe = &p->ae[p->c - 1];
    p->c--;
    pe->s = s;
    pe->pv = pv;
    pe->h = h;
    pe->next = p->ap[ih];
    p->ap[ih] = pe;
}
