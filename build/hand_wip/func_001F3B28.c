typedef unsigned long ulong;
struct P { char pad[0x40]; int v40; char pad2[0x148 - 0x44]; ulong fl; };
int func_001A61A0(struct P *);
void func_001D6378(struct P *);
void func_001D6310(struct P *);
static inline int GetFl(int v) { return ((v ^ 1) & 1) ? *(int *)v : v; }
static inline void SetFl(struct P *p, int f) { int v = p->v40; if ((v ^ 1) & 1) *(int *)v |= f; else p->v40 = v | f; }
static inline void ClrFl(struct P *p, int f) { int v = p->v40; if ((v ^ 1) & 1) *(int *)v &= ~f; else p->v40 = v & ~f; }
void func_001F3B28(struct P *p, int f)
{
    int fl = GetFl(p->v40);
    if (f) {
        if (fl & 8) return;
        SetFl(p, 8);
        if ((p->fl & (1L << 35)) && func_001A61A0(p)) func_001D6378(p);
    } else {
        if (!(fl & 8)) return;
        ClrFl(p, 8);
        func_001D6310(p);
    }
}
