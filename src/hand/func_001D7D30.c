struct B { int c; unsigned char *pb; };
struct Q { char pad[0x5400]; int n5400; int n5404; };
static inline int Sum(unsigned char *pb, unsigned int n) { int sum = 0; while (n) { sum += *pb++; n--; } return sum; }
int func_001D7D30(struct B *p, struct Q *q) {
    int sum = Sum(p->pb, p->c * 10);
    return *(unsigned short *)(p->pb + p->c * 10 - 6) == q->n5400 && sum == q->n5404;
}
