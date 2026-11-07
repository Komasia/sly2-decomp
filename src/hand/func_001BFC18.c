typedef int qword __attribute__((mode(TI)));
struct CTX { int a[4]; };
struct REQ { int cb; int align; };
void __10STACKSCOPE(struct CTX *c);
void _$_10STACKSCOPE(struct CTX *c, int n);
void *PvAllocStackImpl__Fi(struct REQ *r);
void func_001AE5A0(void *dst, void *src, int cb);
int FNavBlocked__FP9NAVREGIONG9VU_VECTORT1i(void *ctx, qword a, qword b, int n);
static __inline__ void *PvAllocReq(struct REQ *preq, int cb, int nKind) { preq->cb = cb; preq->align = nKind; return PvAllocStackImpl__Fi(preq); }
// name: SafeHouse port (SmoothNav)
void SmoothNav__FP9NAVREGIONPiPPG9VU_VECTOR(void *ctx, int *pc, qword **ap)
{
    struct CTX c;
    struct REQ req;
    qword **tmp, **prev, **cur, **next, **end;
    int n, k;
    __10STACKSCOPE(&c);
    n = *pc;
    end = ap + n;
    tmp = PvAllocReq(&req, n * 4, 0x10);
    tmp[0] = ap[0];
    k = 1;
    prev = ap;
    cur = ap + 1;
    next = ap + 2;
    while (next < end) {
        if (FNavBlocked__FP9NAVREGIONG9VU_VECTORT1i(ctx, **prev, **next, 0)) {
            tmp[k] = *cur;
            prev = cur;
            cur = next++;
            k++;
        } else {
            cur = next++;
        }
    }
    tmp[k] = ap[n - 1];
    k++;
    if (k < n && k >= 3) SmoothNav__FP9NAVREGIONPiPPG9VU_VECTOR(ctx, &k, tmp);
    func_001AE5A0(ap, tmp, k * 4);
    *pc = k;
    _$_10STACKSCOPE(&c, 2);
}
