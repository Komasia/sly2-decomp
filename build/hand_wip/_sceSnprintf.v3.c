// v3 (Claude agent): aligned 39 (v2 53): next: written `c = *fmt; if (c) fmt++;` (target tests c in a1 at the tail; 841 vs 837 insns: c now split into a1/a3 copies after each load, target keeps c in a1 + test copy v0 + dispatch copy a2).
// v2: aligned 53 (v1 57): digit accumulate written i = i * 10 + ((char)c - '0'); matches target temp a0.
// WIP (Claude agent): 834/837 insns, difflib ratio ~0.95 (positional 812 differ = 3-insn shift). Left: loop top/tail char regs
// (target: test value in v0 copied to c in a1; tail 'if (*fmt) fmt++' via a1), default-case (char)c==0 test, '.' case ori order,
// digit accumulate reg (a0 temp), and one prefix-loop nop. Keys found: each numeric case ends with its own
// 'start = cp + 1; size = end - cp; goto out;'; 'stop' is cp itself; c is int loaded zero-extended with (char)c uses.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef char *va_list;
#define va_arg(ap, T) (*(T *)((ap += 8) - 8))
typedef int (*PutFunc)(void *, int *, int);
int printfloat(PutFunc put, void *arg, int *w, double d);

int _sceSnprintf(PutFunc put, void *arg, int n, const unsigned char *fmt, va_list ap)
{
    char buf[32];
    char prefix[32];
    char *end;
    char *cp;
    char *start;
    const char *digits;
    int *pn;
    int flags;
    int width;
    int prec;
    int plen;
    int total;
    int size;
    int i;
    int pad;
    int c;
    long v;
    unsigned long u;
    char *s;
    float f;

    end = &buf[31];
    total = 0;
    while ((c = *fmt) != 0) {
        pn = &n;
        flags = 0;
        width = 0;
        prec = 0;
        plen = 0;
        if ((char)c != '%') goto lit;
    again:
        fmt++;
        c = *fmt;
        switch ((char)c) {
        case '-': flags |= 1; goto again;
        case '+': flags |= 2; goto again;
        case '0': flags |= 4; goto again;
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            i = 0;
            do {
                i = i * 10 + ((char)c - '0');
                c = *++fmt;
            } while (c >= '0' && c <= '9');
            width = i;
        num:
            if (c == 0) goto next;
            fmt--;
            goto again;
        case '.':
            flags |= 0x20;
            fmt++;
            if ((char)*fmt == '*') {
                i = va_arg(ap, int);
                prec = i < -1 ? -1 : i;
                goto again;
            }
            c = *fmt;
            i = 0;
            while (c >= '0' && c <= '9') {
                i = i * 10 + ((char)c - '0');
                c = *++fmt;
            }
            prec = i < -1 ? -1 : i;
            goto num;
        case ' ': flags |= 8; goto again;
        case '#': flags |= 0x10; goto again;
        case 'l': flags |= 0x40; goto again;
        case 'h': flags |= 0x80; goto again;
        case 'o':
            if (flags & 0x40) u = va_arg(ap, unsigned long);
            else if (flags & 0x80) u = va_arg(ap, unsigned short);
            else u = va_arg(ap, unsigned int);
            cp = end;
            if (u == 0) {
                if (!(flags & 0x20) || prec != 0) *cp-- = '0';
            } else {
                do {
                    *cp-- = (u & 7) + '0';
                    u >>= 3;
                } while (u);
                if (flags & 0x10) *cp-- = '0';
            }
            start = cp + 1;
            size = end - cp;
            goto out;
        case 'x':
            digits = "0123456789abcdef";
            if (flags & 0x10) {
                prefix[0] = '0';
                prefix[1] = 'x';
                plen = 2;
            }
            goto hex;
        case 'X':
            digits = "0123456789ABCDEF";
            if (flags & 0x10) {
                prefix[0] = '0';
                prefix[1] = 'X';
                plen = 2;
            }
        hex:
            if (flags & 0x40) u = va_arg(ap, unsigned long);
            else if (flags & 0x80) u = va_arg(ap, unsigned short);
            else u = va_arg(ap, unsigned int);
            cp = end;
            if (u == 0) {
                plen = 0;
                if (!(flags & 0x20) || prec != 0) *cp-- = '0';
            } else {
                do {
                    *cp-- = digits[u & 0xF];
                    u >>= 4;
                } while (u);
            }
            start = cp + 1;
            size = end - cp;
            goto out;
        case 'd':
        case 'i':
            if (flags & 0x40) v = va_arg(ap, long);
            else if (flags & 0x80) v = va_arg(ap, short);
            else v = va_arg(ap, int);
            cp = end;
            if (v >= 0) {
                if (flags & 2) {
                    prefix[0] = '+';
                    plen = 1;
                } else if (flags & 8) {
                    prefix[0] = ' ';
                    plen = 1;
                }
            } else {
                prefix[0] = '-';
                plen = 1;
            }
            if (v == 0) {
                if (!(flags & 0x20) || prec != 0) *cp-- = '0';
            } else {
                if (v < 0) v = -v;
                while (v) {
                    *cp-- = v % 10 + '0';
                    v /= 10;
                }
            }
            start = cp + 1;
            size = end - cp;
            goto out;
        case 'u':
            if (flags & 0x40) u = va_arg(ap, unsigned long);
            else if (flags & 0x80) u = va_arg(ap, unsigned short);
            else u = va_arg(ap, unsigned int);
            cp = end;
            if (u == 0) {
                if (!(flags & 0x20) || prec != 0) *cp-- = '0';
            } else {
                do {
                    *cp-- = u % 10 + '0';
                    u /= 10;
                } while (u);
            }
            start = cp + 1;
            size = end - cp;
            goto out;
        case 'e':
        case 'f':
            f = va_arg(ap, double);
            if (f == 0) {
                total += put(arg, pn, '0');
            } else {
                total += printfloat(put, arg, pn, f);
            }
            goto next;
        case 's':
            s = va_arg(ap, char *);
            if (s == 0) {
                put(arg, pn, '(');
                put(arg, pn, 'n');
                put(arg, pn, 'u');
                put(arg, pn, 'l');
                put(arg, pn, 'l');
                put(arg, pn, ')');
                goto next;
            }
            cp = s;
            if (flags & 0x20) {
                for (i = 0; i < prec && *cp++; i++)
                    ;
                size = i;
            } else {
                for (size = 0; *cp; cp++)
                    size++;
            }
            start = s;
            goto out;
        case 'c':
            cp = end;
            v = va_arg(ap, char);
            flags |= 0x100;
            prec = 1;
            *cp-- = v;
            start = cp + 1;
            size = end - cp;
            goto out;
        case 'p':
            u = va_arg(ap, unsigned int);
            digits = "0123456789abcdef";
            cp = end;
            if (u == 0) {
                if (!(flags & 0x20) || prec != 0) *cp-- = '0';
            } else {
                do {
                    *cp-- = digits[u & 0xF];
                    u >>= 4;
                } while (u);
            }
            prefix[0] = '0';
            prefix[1] = 'x';
            plen = 2;
            start = cp + 1;
            size = end - cp;
            goto out;
        default:
            if ((char)c == 0) goto next;
            cp = end;
            flags |= 0x100;
            prec = 1;
            *cp-- = (char)c;
            break;
        }
        size = end - cp;
        start = cp + 1;
    out:
        if (size < prec) prec -= size;
        else prec = 0;
        width = width - size - plen - prec;
        cp = start + size;
        if (flags & 0x100)
            pad = (flags & 4) && width > 0 ? '0' : ' ';
        else
            pad = (flags & 0x24) == 4 && width > 0 ? '0' : ' ';
        if (flags & 1) {
            for (i = 0; i < plen; i++) total += put(arg, pn, prefix[i]);
            for (i = 0; i < prec; i++) total += put(arg, pn, '0');
            while (start < cp) total += put(arg, pn, *start++);
            for (i = 0; i < width; i++) total += put(arg, pn, ' ');
        } else if (flags & 4) {
            if (pad == '0') {
                for (i = 0; i < plen; i++) total += put(arg, pn, prefix[i]);
                for (i = 0; i < width; i++) total += put(arg, pn, pad);
            } else {
                for (i = 0; i < width; i++) total += put(arg, pn, pad);
                for (i = 0; i < plen; i++) total += put(arg, pn, prefix[i]);
            }
            for (i = 0; i < prec; i++) total += put(arg, pn, '0');
            while (start < cp) total += put(arg, pn, *start++);
        } else {
            for (i = 0; i < width; i++) total += put(arg, pn, pad);
            for (i = 0; i < plen; i++) total += put(arg, pn, prefix[i]);
            for (i = 0; i < prec; i++) total += put(arg, pn, '0');
            while (start < cp) total += put(arg, pn, *start++);
        }
        goto next;
    lit:
        if ((char)c == 0) goto next;
        total += put(arg, pn, (char)c);
    next:
        c = *fmt;
        if (c) fmt++;
    }
    put(arg, &n, 0);
    return total;
}
