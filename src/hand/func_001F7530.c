int GrfAloXpBytes__FP3ALOUi(void *p, void *q);
struct N { char pad[0x10]; struct N *next; };
// name: SafeHouse port (PaloXpFilter)
struct N *PaloXpFilter__FP3ALOUi(struct N *p, void *q)
{
    for (; p; p = p->next) {
        if (GrfAloXpBytes__FP3ALOUi(p, q))
            return p;
    }
    return 0;
}
