/* BuildJobHelp (SafeHouse shop.cpp): rebuild Job Help's rows (their part handles released first) from the tasks
 * (func_00165C98, sorted by func_00165C28): page 0 lists each open job (a task's +0x7C, with a title +0x6C) once,
 * selecting the job shown before; page 1 lists the shown job's tasks that have a text (+0x5C), stopping by their
 * +0x54 state. */
struct FRAME {
    int a;
    FRAME();
    ~FRAME();
};
struct SO {
    char pad0[0x54];
    int x54;
    char pad58[0x5C - 0x58];
    int x5C;
    char pad60[0x6C - 0x60];
    int x6C;
    char pad70[0x7C - 0x70];
    SO *x7C;
};
struct E { SO *o; int a; int b; };
struct OBJ {
    char pad0[0x24];
    void *x24;
    char pad28[0x40 - 0x28];
    int x40;
    char pad44[0x48 - 0x44];
    int n;
    E ae[0x10];
    int x10C;
    SO *x110;
    int x114;
    int x118;
};
extern "C" {
void ResetScreenObjPart__FP2LOi(void *, int);
void s1_memset(void *, int, unsigned int) asm("memset");
void func_00165C98(int *, SO ***);
void qsort(void *, int, int, int (*)(const void *, const void *)) asm("qsort");
int func_00165C28(const void *, const void *);
int NJobOpen(SO *) asm("NJobOpen__FP3JOB");
void s1_memmove(void *, void *, unsigned int) asm("memmove");
void func_001DCE90(OBJ *, int);
}
// name: SafeHouse port (BuildJobHelp)
extern "C" void BuildJobHelp__FPv(OBJ *p)
{
    for (int i = 0; i < p->n; i++) {
        E *e = &p->ae[i];
        if (e->a != -1) {
            ResetScreenObjPart__FP2LOi(p->x24, e->a);
            e->a = -1;
        }
        if (e->b != -1) {
            ResetScreenObjPart__FP2LOi(p->x24, e->b);
            e->b = -1;
        }
    }
    p->x118 = 0;
    p->n = 0;
    s1_memset(p->ae, 0, p->n * sizeof(E));
    FRAME frame;
    int c;
    SO **aso;
    func_00165C98(&c, &aso);
    qsort(aso, c, 4, func_00165C28);
    switch (p->x40) {
    case 0: {
        SO *last = 0;
        for (int i = 0; i < c; i++) {
            SO *so = aso[i]->x7C;
            if (so && last != so) {
                last = so;
                if (NJobOpen(so) > 0 && so->x6C != -1) {
                    E *e = &p->ae[p->n++];
                    e->o = so;
                    e->b = -1;
                    e->a = -1;
                    if (p->x110 == so)
                        p->x118 = e - p->ae;
                }
            }
        }
        break;
    }
    case 1: {
        int flag = 0;
        for (int i = 0; i < c; i++) {
            SO *so = aso[i];
            if (p->x110 == so->x7C && so->x5C != -1) {
                if (flag && !so->x54)
                    break;
                E *e = &p->ae[p->n++];
                e->o = so;
                e->b = -1;
                e->a = -1;
                if (so->x54 == 1)
                    flag = 1;
                if (!so->x54)
                    break;
            }
        }
        break;
    }
    }
    if (p->n > p->x10C) {
        s1_memmove(p->ae, &p->ae[p->n - p->x10C], p->x10C * sizeof(E));
        int d = p->n - p->x10C;
        if (d < p->x118)
            p->x118 -= d;
        else
            p->x118 = 0;
        p->n = p->x10C;
    }
    func_001DCE90(p, p->x118);
}
