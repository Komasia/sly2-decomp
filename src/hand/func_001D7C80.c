struct B { int c; unsigned char *pb; };
struct Q { char pad[0x5400]; int n5400; int n5404; };
void *func_002333B4(void *p, int n, int cb);
static inline int Sum(unsigned char *pb, unsigned int n) { int sum = 0; while (n) { sum += *pb++; n--; } return sum; }
void func_001D7C80(struct B *p, struct Q *q) {
    int sum = Sum(p->pb, p->c * 10);
    int n = *(unsigned short *)(p->pb + p->c * 10 - 6);
    if (n == q->n5400 && sum == q->n5404) return;
    func_002333B4(q, 0, 0x5400);
    q->n5400 = n;
    q->n5404 = sum;
}
